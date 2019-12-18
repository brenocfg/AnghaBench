#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {scalar_t__ ah_devid; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 struct ieee80211_channel const* AH_NULL ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 scalar_t__ AR5211_DEVID ; 
 int /*<<< orphan*/  AR5211_PHY_MODE ; 
 int AR5211_PHY_MODE_CCK ; 
 int AR5211_PHY_MODE_OFDM ; 
 int AR5211_PHY_MODE_RF2GHZ ; 
 int AR5211_PHY_MODE_RF5GHZ ; 
 int AR_PHY_FC_TURBO_MODE ; 
 int AR_PHY_FC_TURBO_SHORT ; 
 int /*<<< orphan*/  AR_PHY_PLL_CTL ; 
 int AR_PHY_PLL_CTL_40 ; 
 int AR_PHY_PLL_CTL_44 ; 
 int /*<<< orphan*/  AR_PHY_TURBO ; 
 int AR_RC_BB ; 
 int AR_RC_MAC ; 
 int AR_RC_PCI ; 
 int DELAY_PLL_SETTLE ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5211SetPowerMode (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5211SetResetReg (struct ath_hal*,int) ; 

HAL_BOOL
ar5211ChipReset(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	if (!ar5211SetPowerMode(ah, HAL_PM_AWAKE, AH_TRUE))
		return AH_FALSE;

	/* NB: called from attach with chan null */
	if (chan != AH_NULL) {
		/* Set CCK and Turbo modes correctly */
		OS_REG_WRITE(ah, AR_PHY_TURBO, IEEE80211_IS_CHAN_TURBO(chan) ?
		    AR_PHY_FC_TURBO_MODE | AR_PHY_FC_TURBO_SHORT : 0);
		if (IEEE80211_IS_CHAN_B(chan)) {
			OS_REG_WRITE(ah, AR5211_PHY_MODE,
			    AR5211_PHY_MODE_CCK | AR5211_PHY_MODE_RF2GHZ);
			OS_REG_WRITE(ah, AR_PHY_PLL_CTL, AR_PHY_PLL_CTL_44);
			/* Wait for the PLL to settle */
			OS_DELAY(DELAY_PLL_SETTLE);
		} else if (AH_PRIVATE(ah)->ah_devid == AR5211_DEVID) {
			OS_REG_WRITE(ah, AR_PHY_PLL_CTL, AR_PHY_PLL_CTL_40);
			OS_DELAY(DELAY_PLL_SETTLE);
			OS_REG_WRITE(ah, AR5211_PHY_MODE,
			    AR5211_PHY_MODE_OFDM | (IEEE80211_IS_CHAN_2GHZ(chan) ?
				AR5211_PHY_MODE_RF2GHZ :
				AR5211_PHY_MODE_RF5GHZ));
		}
	}

	/*
	 * Reset the HW - PCI must be reset after the rest of the
	 * device has been reset
	 */
	if (!ar5211SetResetReg(ah, AR_RC_MAC | AR_RC_BB | AR_RC_PCI))
		return AH_FALSE;
	OS_DELAY(2100);	   /* 8245 @ 96Mhz hangs with 2000us. */

	/* Bring out of sleep mode (AGAIN) */
	if (!ar5211SetPowerMode(ah, HAL_PM_AWAKE, AH_TRUE))
		return AH_FALSE;

	/* Clear warm reset register */
	return ar5211SetResetReg(ah, 0);
}