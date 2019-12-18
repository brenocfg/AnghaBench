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
typedef  int u_int ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_EEP_AMODE ; 
 int /*<<< orphan*/  AR_EEP_BMODE ; 
 int /*<<< orphan*/  AR_EEP_TURBO5DISABLE ; 
 int HAL_MODE_108A ; 
 int HAL_MODE_11A ; 
 int HAL_MODE_11B ; 
 int HAL_MODE_TURBO ; 
 scalar_t__ ath_hal_eepromGetFlag (struct ath_hal*,int /*<<< orphan*/ ) ; 

u_int
ar5211GetWirelessModes(struct ath_hal *ah)
{
	u_int mode = 0;

	if (ath_hal_eepromGetFlag(ah, AR_EEP_AMODE)) {
		mode = HAL_MODE_11A;
		if (!ath_hal_eepromGetFlag(ah, AR_EEP_TURBO5DISABLE))
			mode |= HAL_MODE_TURBO | HAL_MODE_108A;
	}
	if (ath_hal_eepromGetFlag(ah, AR_EEP_BMODE))
		mode |= HAL_MODE_11B;
	return mode;
}