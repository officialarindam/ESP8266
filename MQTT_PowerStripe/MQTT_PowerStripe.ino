//all on state or payload is 1 and off state payload is 0
//please change the variables as per your need

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Bounce2.h>
void callback(char* topic, byte* payload, unsigned int length);
#define MQTT_SERVER "mqtt broker address"                   //need to change before flashing
#define MQTT_USERNAME "mqtt broker username"                    //need to change before flashing
#define MQTT_PASSWORD "mqtt broker password"                    //need to change before flashing
#define LAST_WILL_TOPIC "last will topic"                   //need to change before flashing
#define SOCKET1_COMMAND_TOPIC "socket1 command topic"                   //need to change before flashing
#define SOCKET1_STAT_TOPIC "socket1 state topic"                    //need to change before flashing
#define SOCKET2_COMMAND_TOPIC "socket2 command topic"                   //need to change before flashing
#define SOCKET2_STAT_TOPIC "socket2 state topic"                    //need to change before flashing
#define SOCKET3_COMMAND_TOPIC "socket3 command topic"                   //need to change before flashing
#define SOCKET3_STAT_TOPIC "socket3 state topic"                    //need to change before flashing
#define SOCKET4_COMMAND_TOPIC "socket4 command topic"                   //need to change before flashing
#define SOCKET4_STAT_TOPIC "socket4 state topic"                    //need to change before flashing
const char* ssid = "wifi ssid";                   //need to change before flashing
const char* password = "wifi password";                   //need to change before flashing
const int switchPin1 = D1;                    //need to change before flashing
const int switchPin2 = D2;                    //need to change before flashing
const int switchPin3 = D3;                    //need to change before flashing
const int switchPin4 = D4;                    //need to change before flashing
const int buttonPin1 = D5;                    //need to change before flashing
const int buttonPin2 = D6;                    //need to change before flashing
const int buttonPin3 = D7;                    //need to change before flashing
const int buttonPin4 = D8;                    //need to change before flashing
Bounce myButton1 = Bounce();
Bounce myButton2 = Bounce();
Bounce myButton3 = Bounce();
Bounce myButton4 = Bounce();
WiFiClient wifiClient;
PubSubClient client(MQTT_SERVER, 1883, callback, wifiClient);





void setup() {
  pinMode(switchPin1, OUTPUT);
  digitalWrite(switchPin1, LOW);
  pinMode(switchPin2, OUTPUT);
  digitalWrite(switchPin2, LOW);
  pinMode(switchPin3, OUTPUT);
  digitalWrite(switchPin3, LOW);
  pinMode(switchPin4, OUTPUT);
  digitalWrite(switchPin4, LOW);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  myButton1.attach(buttonPin1);
  myButton1.interval(5);
  myButton2.attach(buttonPin2);
  myButton2.interval(5);
  myButton3.attach(buttonPin3);
  myButton3.interval(5);
  myButton4.attach(buttonPin4);
  myButton4.interval(5);
  Serial.begin(115200);
  delay(100);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  reconnect();
  delay(2000);
}





void loop(){
  if (!client.connected() && WiFi.status() == 3) {reconnect();}
  client.loop();
  checkButton();
  delay(10);
}






void callback(char* topic, byte* payload, unsigned int length) {
  String topicStr = topic;
  Serial.println("Callback update.");
  Serial.print("Topic: ");
  Serial.println(topicStr);
   if (topicStr == SOCKET1_COMMAND_TOPIC) 
    {
     if(payload[0] == '1'){
       digitalWrite(switchPin1, HIGH);
       client.publish(SOCKET1_STAT_TOPIC, "1", true);
       }
     else if (payload[0] == '0'){
       digitalWrite(switchPin1, LOW);
       client.publish(SOCKET1_STAT_TOPIC, "0", true);
       }
     }
     else if (topicStr == SOCKET2_COMMAND_TOPIC) 
     {
     if(payload[0] == '1'){
       digitalWrite(switchPin2, HIGH);
       client.publish(SOCKET2_STAT_TOPIC, "1", true);
       }
     else if (payload[0] == '0'){
       digitalWrite(switchPin2, LOW);
       client.publish(SOCKET2_STAT_TOPIC, "0", true);
       }
     }
     else if (topicStr == SOCKET3_COMMAND_TOPIC) 
     {
     if(payload[0] == '1'){
       digitalWrite(switchPin3, HIGH);
       client.publish(SOCKET3_STAT_TOPIC, "1", true);
       }
     else if (payload[0] == '0'){
       digitalWrite(switchPin3, LOW);
       client.publish(SOCKET3_STAT_TOPIC, "0", true);
       }
     }
     else if (topicStr == SOCKET4_COMMAND_TOPIC) 
     {
     if(payload[0] == '1'){
       digitalWrite(switchPin4, HIGH);
       client.publish(SOCKET4_STAT_TOPIC, "1", true);
       }
     else if (payload[0] == '0'){
       digitalWrite(switchPin4, LOW);
       client.publish(SOCKET4_STAT_TOPIC, "0", true);
       }
    }
}





void checkButton(){
  static boolean isOn1 = false;
  if(myButton1.update() && myButton1.read() == HIGH){
    if(isOn1 == false){
      client.publish(SOCKET1_COMMAND_TOPIC, "1", true);
      Serial.print("Button1: ");
      Serial.println(isOn1);
      isOn1 = true;
    }
    else{
      client.publish(SOCKET1_COMMAND_TOPIC, "0", true);
      Serial.print("Button1: ");
      Serial.println(isOn1);
      isOn1 = false;
    }
  }
  static boolean isOn2 = false;
  if(myButton2.update() && myButton2.read() == HIGH){
    if(isOn2 == false){
      client.publish(SOCKET2_COMMAND_TOPIC, "1", true);
      Serial.print("Button2: ");
      Serial.println(isOn2);
      isOn2 = true;
    }
    else{
      client.publish(SOCKET2_COMMAND_TOPIC, "0", true);
      Serial.print("Button2: ");
      Serial.println(isOn2);
      isOn2 = false;
    }
  }
  static boolean isOn3 = false;
  if(myButton3.update() && myButton3.read() == HIGH){
    if(isOn3 == false){
      client.publish(SOCKET3_COMMAND_TOPIC, "1", true);
      Serial.print("Button3: ");
      Serial.println(isOn3);
      isOn3 = true;
    }
    else{
      client.publish(SOCKET3_COMMAND_TOPIC, "0", true);
      Serial.print("Button3: ");
      Serial.println(isOn3);
      isOn3 = false;
    }
  }
  static boolean isOn4 = false;
  if(myButton4.update() && myButton4.read() == HIGH){
    if(isOn4 == false){
      client.publish(SOCKET4_COMMAND_TOPIC, "1", true);
      Serial.print("Button4: ");
      Serial.println(isOn4);
      isOn4 = true;
    }
    else{
      client.publish(SOCKET4_COMMAND_TOPIC, "0", true);
      Serial.print("Button4: ");
      Serial.println(isOn4);
      isOn4 = false;
    }
  }
}





void reconnect() {
      delay(1000);
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Connecting to ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  if(WiFi.status() == WL_CONNECTED){
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      String clientName;
      clientName += "esp8266-";
      uint8_t mac[6];
      WiFi.macAddress(mac);
      clientName += macToStr(mac);
      if (client.connect((char*) clientName.c_str(),MQTT_USERNAME, MQTT_PASSWORD, LAST_WILL_TOPIC, 0, 1, "0")) {
        Serial.print("\tMQTT Connected");
        client.publish(LAST_WILL_TOPIC, "1", true);
        client.subscribe(SOCKET1_COMMAND_TOPIC);
        client.subscribe(SOCKET2_COMMAND_TOPIC);
        client.subscribe(SOCKET3_COMMAND_TOPIC);
        client.subscribe(SOCKET4_COMMAND_TOPIC);
      }
      else{Serial.println("\tFailed."); abort();}
    }
  }
}



String macToStr(const uint8_t* mac){

  String result;

  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);

    if (i < 5){
      result += ':';
    }
  }

  return result;
}



