#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;

/* Variables and functions */
#define  RT2860_RF_2720 140 
#define  RT2860_RF_2750 139 
#define  RT2860_RF_2820 138 
#define  RT2860_RF_2850 137 
#define  RT3070_RF_2020 136 
#define  RT3070_RF_3020 135 
#define  RT3070_RF_3021 134 
#define  RT3070_RF_3022 133 
#define  RT3070_RF_3052 132 
#define  RT3593_RF_3053 131 
#define  RT5390_RF_5370 130 
#define  RT5390_RF_5372 129 
#define  RT5592_RF_5592 128 

__attribute__((used)) static const char *
run_get_rf(uint16_t rev)
{
	switch (rev) {
	case RT2860_RF_2820:	return "RT2820";
	case RT2860_RF_2850:	return "RT2850";
	case RT2860_RF_2720:	return "RT2720";
	case RT2860_RF_2750:	return "RT2750";
	case RT3070_RF_3020:	return "RT3020";
	case RT3070_RF_2020:	return "RT2020";
	case RT3070_RF_3021:	return "RT3021";
	case RT3070_RF_3022:	return "RT3022";
	case RT3070_RF_3052:	return "RT3052";
	case RT3593_RF_3053:	return "RT3053";
	case RT5592_RF_5592:	return "RT5592";
	case RT5390_RF_5370:	return "RT5370";
	case RT5390_RF_5372:	return "RT5372";
	}
	return ("unknown");
}