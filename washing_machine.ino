//Simple Smart Washing Machine


//define pins
const int LED              = 2;   //LED on board 
const int startButton      = 23;  //button       
const int lockDoor         = 22;  //button 
const int waterValve       = 14;  //LED green
const int upperLevelSensor = 21;  //button
const int heater           = 12;  //LED red
const int motorRight       = 32;  //LED yellow
const int motorLeft        = 33;  //LED red
const int disChargePump    = 25;  //LED green
const int lowerLevelSensor = 19;  //button
const int ledWarning       = 26;  //LED red

//various state of inputs
int buttonState     = HIGH;
int doorState       = HIGH;
int upperLevelState = HIGH;
int lowerLevelState = HIGH;

void setup() {
  
	Serial.begin(9600);

	pinMode(LED, OUTPUT);
	pinMode(startButton, INPUT_PULLUP);
	pinMode(lockDoor, INPUT_PULLUP);
	pinMode(waterValve, OUTPUT);
	pinMode(upperLevelSensor, INPUT_PULLUP);
	pinMode(heater, OUTPUT);
	pinMode(motorRight, OUTPUT);
	pinMode(motorLeft, OUTPUT);
	pinMode(disChargePump, OUTPUT);
	pinMode(lowerLevelSensor, INPUT_PULLUP);
	pinMode(ledWarning, OUTPUT);

}

void loop() {
   
	buttonState = digitalRead(startButton);
	//start
	if(buttonState == LOW)
	{
		digitalWrite(LED, HIGH);
		//checking door
		delay(2000);
		doorState = digitalRead(lockDoor);
		if(doorState == LOW)
		{
			//openning water valve till the cab fills
			while(upperLevelState == HIGH)
			{
				digitalWrite(waterValve, HIGH);
				upperLevelState = digitalRead(upperLevelSensor);
				digitalWrite(waterValve, LOW);
			}

			//the heater switches on
			digitalWrite(heater, HIGH);
			delay(5000);
			digitalWrite(heater, LOW);

			//washing 
			for(int i = 0; i < 5; i++)
			{
				//turn right        
				digitalWrite(motorRight, HIGH);
				delay(3000);
				digitalWrite(motorRight, LOW);
				//turn left
				digitalWrite(motorLeft, HIGH);
				delay(3000);
				digitalWrite(motorLeft, LOW);
			}

			//discharging the water till the cap is empty
			while(lowerLevelState == HIGH)
			{
				digitalWrite(disChargePump, HIGH);
				lowerLevelState = digitalRead(lowerLevelSensor);
				digitalWrite(disChargePump, LOW);
			}

			//alarm to finish
			for(int i = 0; i < 3; i++)	
			{
				digitalWrite(ledWarning, HIGH);
				delay(1000);
				digitalWrite(ledWarning, LOW);
				delay(1000);       
			}
		} else 
		{
			digitalWrite(ledWarning, HIGH);
    	}    
	}
	//turn off the machine	
	digitalWrite(LED, LOW); 
}
