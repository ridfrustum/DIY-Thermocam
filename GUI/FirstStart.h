/*
* First Start Menu
*/

/* Show welcome Screen for the first start procedure */
void welcomeScreen() {
	display.fillScr(127, 127, 127);
	display.setBackColor(127, 127, 127);
	display.setFont(bigFont);
	display.printC("Welcome to the", CENTER, 20);
	display.printC("DIY-Thermocam", CENTER, 60, VGA_YELLOW);
	display.setFont(smallFont);
	display.printC("This is the first time setup.", CENTER, 110);
	display.printC("It will guide you through", CENTER, 140);
	display.printC("the basic settings.", CENTER, 170);
	display.printC("Please touch screen", CENTER, 210, VGA_YELLOW);
	//Wait for touch press
	while (!touch.touched());
	//Touch release again
	while (touch.touched());
}

/* Shows an info screen during the first start procedure */
void infoScreen(String* text, bool Continue) {
	display.fillScr(127, 127, 127);
	display.setBackColor(127, 127, 127);
	display.setFont(bigFont);
	display.printC(text[0], CENTER, 20, VGA_YELLOW);
	display.setFont(smallFont);
	display.printC(text[1], CENTER, 55);
	display.printC(text[2], CENTER, 80);
	display.printC(text[3], CENTER, 105);
	display.printC(text[4], CENTER, 130);
	if (Continue) {
		display.printC(text[5], CENTER, 155);
		display.printC(text[6], CENTER, 180);
		display.printC("Please touch screen", CENTER, 212, VGA_YELLOW);
		//Wait for touch press
		while (!touch.touched());
		//Touch release again
		while (touch.touched());
	}
	else {
		display.printC(text[5], CENTER, 180);
		display.printC(text[6], CENTER, 205);
	}
}

/* Setting screen for the time and date */
void timeDateScreen() {
	String text[7];
	text[0] = "Set Time & Date";
	text[1] = "In the next screen, you have";
	text[2] = "to set the time and date so ";
	text[3] = "that it matches your current";
	text[4] = "time zone. This only has to be";
	text[5] = "done once, as the coin cell battery";
	text[6] = "powers the real-time-clock permanent.";
	infoScreen(text);
	//Adjust Time & Date settings
	setTime(12, 30, 30, 15, 6, 2016);
	timeAndDateMenu(true);
	timeAndDateMenuHandler(true);
}

/* Setting screen for the temperature format */
void tempFormatScreen() {
	String text[7];
	text[0] = "Set Temp. Format";
	text[1] = "In the next screen, you have";
	text[2] = "to set the temperature format ";
	text[3] = "for the temperature display.";
	text[4] = "Choose either Celcius or";
	text[5] = "Fahrenheit, the conversion will";
	text[6] = "be done automatically.";
	infoScreen(text);
	//Temperature format
	tempFormatMenu(true);
}

/* Setting screen for the convert image option */
void convertImageScreen() {
	String text[7];
	text[0] = "Convert image";
	text[1] = "In the next screen, please select";
	text[2] = "if you want to create a bitmap";
	text[3] = "file for every saved thermal";
	text[4] = "image automatically on the device.";
	text[5] = "You can also convert images man-";
	text[6] = "ually in the Load Menu later.";
	infoScreen(text);;
	//Convert image
	convertImageMenu(true);
}

/* Setting screen for the visual image option */
void visualImageScreen() {
	String text[7];
	text[0] = "Visual image";
	text[1] = "In the next screen, choose";
	text[2] = "whether you want to save";
	text[3] = "a visual image together";
	text[4] = "with the thermal image each";
	text[5] = "time. Enable this if you want";
	text[6] = "to create combined images.";
	infoScreen(text);
	//Visual image
	visualImageMenu(true);
}

/* Setting screen for the calibration procedure */
void calibrationScreen() {
	String text[7];
	text[0] = "Calibration process";
	text[1] = "For the raw-to-absolute temp con-";
	text[2] = "version, you have to do a calibration";
	text[3] = "first. Point the device to different ";
	text[4] = "hot and cold objects slowly, so that";
	text[5] = "the objects cover both the spot sensor";
	text[6] = "and the LWIR sensor at once.";
	infoScreen(text);
	//Calibration procedure
	calibrationProcess(true);
}

/* Show the first start complete screen */
void firstStartComplete() {
	String text[7];
	text[0] = "Setup completed !";
	text[1] = "The first-time setup is";
	text[2] = "now complete. Please reboot";
	text[3] = "the device by turning the";
	text[4] = "power switch off and on again.";
	text[5] = "Afterwards, you will be redirected";
	text[6] = "to first start helper.";
	infoScreen(text, false);
	while (true);
}

/* Check if the live mode helper needs to be shown */
bool checkLiveModeHelper() {
	return EEPROM.read(eeprom_liveHelper) != eeprom_setValue;
}

/* Help screen for the first start of live mode */
void liveModeHelper() {
	//Array to store up to 7 lines of text
	String text[7];
	//Hint screen for the live mode #1 
	text[0] = "First time helper";
	text[1] = "To enter the live mode menu,";
	text[2] = "touch the screen. 'Exit' will";
	text[3] = "bring you to the main menu.";
	text[4] = "Pressing the pushbutton on";
	text[5] = "top of the device short takes";
	text[6] = "an image, long records a video.";
	infoScreen(text);
	text[1] = "The device needs one minute";
	text[2] = "to warmup the sensor, the color-";
	text[3] = "bar will be activated afterwards.";
	text[4] = "If you want to lock the limits";
	text[5] = "on the colorbar, touch the screen";
	text[6] = "long until a message is shown.";
	infoScreen(text);
	//Set EEPROM marker to complete
	EEPROM.write(eeprom_liveHelper, eeprom_setValue);
}

/* Shows the completion message for the adjust camera */
void adjustCamComplete() {
	String text[7];
	text[0] = "Adjust completed!";
	text[1] = "The adjust camera setup is";
	text[2] = "now complete. Please reboot";
	text[3] = "the device by turning the";
	text[4] = "power switch off and on again.";
	text[5] = "Afterwards, you will be redirected";
	text[6] = "to the live mode again.";
	infoScreen(text, false);
	while (true);
}


/* Set the EEPROM values to default for the first time */
void stdEEPROMSet() {
	drawMessage((char*) "Flashing spot EEPROM settings..");
	//Set spot maximum temp to 380�C
	mlx90614SetMax();
	//Set spot minimum temp to -70�
	mlx90614SetMin();
	//Set spot filter settings
	mlx90614SetFilter();
	//Set spot emissivity to 0.9
	mlx90614SetEmissivity();
	//Set device EEPROM settings
	EEPROM.write(eeprom_rotationEnabled, false);
	EEPROM.write(eeprom_spotEnabled, true);
	EEPROM.write(eeprom_colorbarEnabled, true);
	EEPROM.write(eeprom_batteryEnabled, false);
	EEPROM.write(eeprom_timeEnabled, false);
	EEPROM.write(eeprom_dateEnabled, false);
	EEPROM.write(eeprom_pointsEnabled, false);
	EEPROM.write(eeprom_storageEnabled, false);
	EEPROM.write(eeprom_displayMode, displayMode_thermal);
	//Set Color Scheme to Rainbow
	EEPROM.write(eeprom_colorScheme, colorScheme_rainbow);
	//Set filter type to box blur
	EEPROM.write(eeprom_filterType, filterType_gaussian);
	//Set mass storage to false
	EEPROM.write(eeprom_massStorage, false);
	//Set current firmware version
	EEPROM.write(eeprom_fwVersion, fwVersion);
	//Set first start marker to true
	EEPROM.write(eeprom_firstStart, eeprom_setValue);
	//Set live helper to false to show it the next time
	EEPROM.write(eeprom_liveHelper, false);
}

/* First start setup*/
void firstStart() {
	//Welcome screen
	welcomeScreen();
	//Hint screen for the time and date settings
	timeDateScreen();
	//Hint screen for temperature format setting
	tempFormatScreen();
	//Hint screen for the convert image settings
	convertImageScreen();
	//Hint screen for the visual image settings
	visualImageScreen();
	//Do the first time calibration
	calibrationScreen();
	//Set EEPROM values
	stdEEPROMSet();
	//Show completion message
	firstStartComplete();
}

/* Check if the first start needs to be done */
bool checkFirstStart() {
	return EEPROM.read(eeprom_firstStart) != eeprom_setValue;
}