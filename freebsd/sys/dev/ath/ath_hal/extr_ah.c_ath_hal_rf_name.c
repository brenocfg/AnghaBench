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
struct ath_hal {int ah_analog5GhzRev; } ;

/* Variables and functions */
#define  AR_RAD2111_SREV_MAJOR 145 
#define  AR_RAD2112_SREV_2_0 144 
#define  AR_RAD2112_SREV_2_1 143 
#define  AR_RAD2112_SREV_MAJOR 142 
#define  AR_RAD2122_SREV_MAJOR 141 
#define  AR_RAD2133_SREV_MAJOR 140 
#define  AR_RAD2316_SREV_MAJOR 139 
#define  AR_RAD2317_SREV_MAJOR 138 
#define  AR_RAD2413_SREV_MAJOR 137 
#define  AR_RAD5111_SREV_MAJOR 136 
#define  AR_RAD5111_SREV_PROD 135 
#define  AR_RAD5112_SREV_2_0 134 
#define  AR_RAD5112_SREV_2_1 133 
#define  AR_RAD5112_SREV_MAJOR 132 
#define  AR_RAD5122_SREV_MAJOR 131 
#define  AR_RAD5133_SREV_MAJOR 130 
#define  AR_RAD5413_SREV_MAJOR 129 
#define  AR_RAD5424_SREV_MAJOR 128 
 int AR_RADIO_SREV_MAJOR ; 

const char *
ath_hal_rf_name(struct ath_hal *ah)
{
	switch (ah->ah_analog5GhzRev & AR_RADIO_SREV_MAJOR) {
	case 0:			/* 5210 */
		return "5110";	/* NB: made up */
	case AR_RAD5111_SREV_MAJOR:
	case AR_RAD5111_SREV_PROD:
		return "5111";
	case AR_RAD2111_SREV_MAJOR:
		return "2111";
	case AR_RAD5112_SREV_MAJOR:
	case AR_RAD5112_SREV_2_0:
	case AR_RAD5112_SREV_2_1:
		return "5112";
	case AR_RAD2112_SREV_MAJOR:
	case AR_RAD2112_SREV_2_0:
	case AR_RAD2112_SREV_2_1:
		return "2112";
	case AR_RAD2413_SREV_MAJOR:
		return "2413";
	case AR_RAD5413_SREV_MAJOR:
		return "5413";
	case AR_RAD2316_SREV_MAJOR:
		return "2316";
	case AR_RAD2317_SREV_MAJOR:
		return "2317";
	case AR_RAD5424_SREV_MAJOR:
		return "5424";

	case AR_RAD5133_SREV_MAJOR:
		return "5133";
	case AR_RAD2133_SREV_MAJOR:
		return "2133";
	case AR_RAD5122_SREV_MAJOR:
		return "5122";
	case AR_RAD2122_SREV_MAJOR:
		return "2122";
	}
	return "????";
}