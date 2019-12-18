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
struct ath_hal_5212 {scalar_t__ ah_enable32kHzClock; } ;
struct ath_hal {int dummy; } ;
typedef  scalar_t__ HAL_OPMODE ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int AH_FALSE ; 
 int /*<<< orphan*/  AR_EEP_32KHZCRYSTAL ; 
 scalar_t__ AUTO_32KHZ ; 
 scalar_t__ HAL_M_HOSTAP ; 
 scalar_t__ USE_32KHZ ; 
 scalar_t__ ath_hal_eepromGetFlag (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5212Use32KHzclock(struct ath_hal *ah, HAL_OPMODE opmode)
{
	if (opmode != HAL_M_HOSTAP) {
		struct ath_hal_5212 *ahp = AH5212(ah);
		return ath_hal_eepromGetFlag(ah, AR_EEP_32KHZCRYSTAL) &&
		       (ahp->ah_enable32kHzClock == USE_32KHZ ||
		        ahp->ah_enable32kHzClock == AUTO_32KHZ);
	} else
		return AH_FALSE;
}