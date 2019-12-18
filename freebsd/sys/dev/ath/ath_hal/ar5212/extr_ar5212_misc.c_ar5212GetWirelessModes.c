#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {scalar_t__ halChanQuarterRate; scalar_t__ halChanHalfRate; } ;
struct TYPE_4__ {scalar_t__ ah_subvendorid; TYPE_1__ ah_caps; } ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_EEP_AMODE ; 
 int /*<<< orphan*/  AR_EEP_BMODE ; 
 int /*<<< orphan*/  AR_EEP_GMODE ; 
 int /*<<< orphan*/  AR_EEP_TURBO2DISABLE ; 
 int /*<<< orphan*/  AR_EEP_TURBO5DISABLE ; 
 scalar_t__ AR_SUBVENDOR_ID_NOG ; 
 int HAL_MODE_108A ; 
 int HAL_MODE_108G ; 
 int HAL_MODE_11A ; 
 int HAL_MODE_11A_HALF_RATE ; 
 int HAL_MODE_11A_QUARTER_RATE ; 
 int HAL_MODE_11B ; 
 int HAL_MODE_11G ; 
 int HAL_MODE_11G_HALF_RATE ; 
 int HAL_MODE_11G_QUARTER_RATE ; 
 int HAL_MODE_TURBO ; 
 scalar_t__ ath_hal_eepromGetFlag (struct ath_hal*,int /*<<< orphan*/ ) ; 

u_int
ar5212GetWirelessModes(struct ath_hal *ah)
{
	u_int mode = 0;

	if (ath_hal_eepromGetFlag(ah, AR_EEP_AMODE)) {
		mode = HAL_MODE_11A;
		if (!ath_hal_eepromGetFlag(ah, AR_EEP_TURBO5DISABLE))
			mode |= HAL_MODE_TURBO | HAL_MODE_108A;
		if (AH_PRIVATE(ah)->ah_caps.halChanHalfRate)
			mode |= HAL_MODE_11A_HALF_RATE;
		if (AH_PRIVATE(ah)->ah_caps.halChanQuarterRate)
			mode |= HAL_MODE_11A_QUARTER_RATE;
	}
	if (ath_hal_eepromGetFlag(ah, AR_EEP_BMODE))
		mode |= HAL_MODE_11B;
	if (ath_hal_eepromGetFlag(ah, AR_EEP_GMODE) &&
	    AH_PRIVATE(ah)->ah_subvendorid != AR_SUBVENDOR_ID_NOG) {
		mode |= HAL_MODE_11G;
		if (!ath_hal_eepromGetFlag(ah, AR_EEP_TURBO2DISABLE))
			mode |= HAL_MODE_108G;
		if (AH_PRIVATE(ah)->ah_caps.halChanHalfRate)
			mode |= HAL_MODE_11G_HALF_RATE;
		if (AH_PRIVATE(ah)->ah_caps.halChanQuarterRate)
			mode |= HAL_MODE_11G_QUARTER_RATE;
	}
	return mode;
}