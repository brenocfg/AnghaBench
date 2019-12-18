#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int /*<<< orphan*/  ic_freq; } ;
struct TYPE_4__ {scalar_t__ ah_force_full_reset; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ah_initPLL ) (struct ath_hal*,struct ieee80211_channel const*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  ah_chipFullSleep; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_3__* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_MARK_CHIPRESET ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_EEP_OL_PWRCTRL ; 
 scalar_t__ AR_SREV_MERLIN (struct ath_hal*) ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  HAL_RESET_POWER_ON ; 
 int /*<<< orphan*/  HAL_RESET_WARM ; 
 int /*<<< orphan*/  OS_MARK (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ahp ; 
 int /*<<< orphan*/  ar5416SetPowerMode (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5416SetResetReg (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5416SetRfMode (struct ath_hal*,struct ieee80211_channel const*) ; 
 scalar_t__ ath_hal_eepromGetFlag (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ath_hal*,struct ieee80211_channel const*) ; 

HAL_BOOL
ar5416ChipReset(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	OS_MARK(ah, AH_MARK_CHIPRESET, chan ? chan->ic_freq : 0);
	/*
	 * Warm reset is optimistic for open-loop TX power control.
	 */
	if (AR_SREV_MERLIN(ah) &&
	    ath_hal_eepromGetFlag(ah, AR_EEP_OL_PWRCTRL)) {
		if (!ar5416SetResetReg(ah, HAL_RESET_POWER_ON))
			return AH_FALSE;
	} else if (ah->ah_config.ah_force_full_reset) {
		if (!ar5416SetResetReg(ah, HAL_RESET_POWER_ON))
			return AH_FALSE;
	} else {
		if (!ar5416SetResetReg(ah, HAL_RESET_WARM))
			return AH_FALSE;
	}

	/* Bring out of sleep mode (AGAIN) */
	if (!ar5416SetPowerMode(ah, HAL_PM_AWAKE, AH_TRUE))
	       return AH_FALSE;

#ifdef notyet
	ahp->ah_chipFullSleep = AH_FALSE;
#endif

	AH5416(ah)->ah_initPLL(ah, chan);

	/*
	 * Perform warm reset before the mode/PLL/turbo registers
	 * are changed in order to deactivate the radio.  Mode changes
	 * with an active radio can result in corrupted shifts to the
	 * radio device.
	 */
	ar5416SetRfMode(ah, chan);

	return AH_TRUE;	
}