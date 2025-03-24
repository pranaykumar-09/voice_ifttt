

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define buzzerPin 0
#define WLAN_SSID ""
#define WLAN_PASS ""
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME " "
#define AIO_KEY " "
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME,
Adafruit_MQTT_Subscribe onoffbutton =
Adafruit_MQTT_Subscribe(&mqtt, " ", MQTT_QOS_1);
void onoffcallback(char *data, uint16_t len) {
  Serial.print("Obtained value : ");
  Serial.println(data);
  if(String(data).equals("ON")){
     digitalWrite(buzzerPin, HIGH);
    }else{
          digitalWrite(buzzerPin, LOW);
       }
}
void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println("Adafruit MQTT demo");
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  onoffbutton.setCallback(onoffcallback);
  mqtt.subscribe(&onoffbutton);
}
void loop() {
    MQTT_connect();
    mqtt.processPackets(10000);
    delay(1000);


}
void MQTT_connect() {
  if (mqtt.connected()) {
  return;
  }
  Serial.println("Connecting to MQTT... ");
  while (mqtt.connect() != 0) {
     Serial.println("Retrying MQTT connection in 10 seconds...");
     mqtt.disconnect();
     delay(2000);
}
Serial.println("MQTT Connected!");

}