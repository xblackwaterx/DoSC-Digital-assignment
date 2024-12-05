// Add your Blynk Template ID and Template Name
#define BLYNK_TEMPLATE_ID "TMPL3QUZgJRKq"  // Replace with your Template ID
#define BLYNK_TEMPLATE_NAME "plant watering system"  
#define BLYNK_PRINT Serial  // Enable serial output for Blynk debug
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Replace with your Template Name

char auth[] = "fZVxsg3PwOW5VUeZDQBB-9izE823kyLN";  // Enter your Auth token
char ssid[] = "Ansh's Oneplus";  // Enter your WIFI name
char pass[] = "truv8955";  // Enter your WIFI password

BlynkTimer timer;  // Create a timer object to manage periodic tasks
bool Relay = 0;

// Define component pins
#define sensor A0  // Pin for soil moisture sensor
#define waterPump D3  // Pin for controlling the water pump (relay)

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);  // Initially turn off the water pump

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Call the function to read soil moisture and send values to Blynk
  timer.setInterval(100L, soilMoistureSensor);  // Set interval for sensor reading
}

// Get the button value from Blynk app
BLYNK_WRITE(V1) {
  Relay = param.asInt();  // Get the relay control value from the Blynk app

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);  // Turn on the motor (relay)
    Serial.println("Motor is ON");
  } else {
    digitalWrite(waterPump, HIGH);  // Turn off the motor (relay)
    Serial.println("Motor is OFF");
  }
}

// Get the soil moisture values and send to Blynk
void soilMoistureSensor() {
    int rawValue = analogRead(sensor);
    Serial.print("Raw Sensor Value: ");
    Serial.println(rawValue);

    // Adjust the range as per your sensor's calibration
    int value = map(rawValue, 200, 800, 0, 100);
    value = constrain(value, 0, 100);

    Blynk.virtualWrite(V0, value);
    Serial.print("Soil Moisture (%): ");
    Serial.println(value);
}


void loop() {
  Blynk.run();  // Run the Blynk library
  timer.run();  // Run the Blynk timer to manage periodic tasks
}
