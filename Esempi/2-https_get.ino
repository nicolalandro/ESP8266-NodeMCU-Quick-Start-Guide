#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "nome_connessione";
const char* password = "password";

const char *fingerprint = "CF 05 98 89 CA FF 8E D8 5E 5C E0 C2 E4 F7 E6 C3 C7 50 DD 5C";
const char *url = "api.github.com";
const char *path = "/";
const int httpsPort = 443;

HTTPClient http;
int httpCode;

void setup() {
  Serial.begin(115200);
  
  connectToWifi();
}

void loop() {
  makeGet();
  
  delay(2000);

}

void makeGet(){
  http.begin(url, httpsPort, path, true, fingerprint);
  httpCode = http.GET();

  if (httpCode > 0) 
  {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    if (httpCode == 200)
    {
      Serial.println(http.getString());
    }
    else if(httpCode == 301){
      Serial.println("\n\t" + http.getString());
    }
    
  } 
  else
  {
    Serial.printf("[HTTP] GET... failed: error code %d", httpCode);
  }
}

void connectToWifi()
{
  Serial.begin(115200);

    // Connect to an existing Wi-Fi network
    WiFi.begin(ssid, password);
    Serial.print("\n\nConnecting");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println(" DONE!");

    Serial.println(WiFi.localIP());
}
