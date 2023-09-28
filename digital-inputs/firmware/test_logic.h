// test_logic.h

#pragma once

#include "cstring"

#define MAX_ANALOG_CHANNELS 16
#define MAX_BOARD_REVS 32
#define index2human(x) ((x) + 1)
#define CAN_FRAME_SIZE 8

bool testEcuDigitalOutput(int testLineIndex, bool isLowSide);

class Counter {
public:
	int canFrameIndex;
	const char *name;
	bool nonZero = false;
};

#define EVENT_ENUM_SIZE 7
#define BUTTON_ENUM_SIZE 3

class CounterStatus {
public:
	Counter eventCounters[EVENT_ENUM_SIZE] = {
		{ 0, "Primary" },
		{ 1, "Secondary" },
		{ 2, "VVT1" },
		{ 3, "VVT2" },
		{ 4, "VVT3" },		
		{ 5, "VVT4" },
		{ 6, "VSS" },					
	};

	Counter buttonCounters[BUTTON_ENUM_SIZE] = {
		{ 0, "BrakePedal" },
		{ 1, "ClutchUp" },
		{ 2, "AcButton" },
	};
};

class AnalogChannelConfig {
public:
	const char *name;
	float mulCoef;	// equal to 'dividerCoef' from the firmware
	float acceptMin, acceptMax;
};

class BoardConfig {
public:
	const char *boardName;
	int desiredEngineConfig;
	uint16_t boardIds[MAX_BOARD_REVS];
	AnalogChannelConfig channels[MAX_ANALOG_CHANNELS];
	bool eventExpected[EVENT_ENUM_SIZE];
	bool buttonExpected[BUTTON_ENUM_SIZE];
};

BoardConfig *getBoardConfigs();
size_t getBoardsCount();

extern BoardConfig *currentBoard;
extern int16_t currentBoardRev;

size_t getDigitalInputStepsCount();
size_t totalStepsNumber();

