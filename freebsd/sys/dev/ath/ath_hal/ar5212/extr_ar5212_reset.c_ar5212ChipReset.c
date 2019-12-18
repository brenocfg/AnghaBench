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
typedef  int uint32_t ;
struct ieee80211_channel {int /*<<< orphan*/  ic_freq; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_MARK_CHIPRESET ; 
 struct ieee80211_channel const* AH_NULL ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int AR_PHY_FC_TURBO_MODE ; 
 int AR_PHY_FC_TURBO_SHORT ; 
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int AR_PHY_MODE_AR5111 ; 
 int AR_PHY_MODE_AR5112 ; 
 int AR_PHY_MODE_CCK ; 
 int AR_PHY_MODE_DYNAMIC ; 
 int AR_PHY_MODE_HALF ; 
 int AR_PHY_MODE_OFDM ; 
 int AR_PHY_MODE_QUARTER ; 
 int AR_PHY_MODE_RF2GHZ ; 
 int AR_PHY_MODE_RF5GHZ ; 
 int /*<<< orphan*/  AR_PHY_PLL_CTL ; 
 int AR_PHY_PLL_CTL_40 ; 
 int AR_PHY_PLL_CTL_40_5112 ; 
 int AR_PHY_PLL_CTL_40_5413 ; 
 int AR_PHY_PLL_CTL_44 ; 
 int AR_PHY_PLL_CTL_44_5112 ; 
 int AR_PHY_PLL_CTL_HALF ; 
 int AR_PHY_PLL_CTL_QUARTER ; 
 int /*<<< orphan*/  AR_PHY_TURBO ; 
 int AR_RC_BB ; 
 int AR_RC_MAC ; 
 int AR_RC_PCI ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_CCK (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_OFDM (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel const*) ; 
 scalar_t__ IS_5413 (struct ath_hal*) ; 
 scalar_t__ IS_RAD5111 (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_MARK (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLL_SETTLE_DELAY ; 
 int /*<<< orphan*/  ar5212SetPowerMode (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5212SetResetReg (struct ath_hal*,int) ; 

HAL_BOOL
ar5212ChipReset(struct ath_hal *ah, const struct ieee80211_channel *chan)
{

	OS_MARK(ah, AH_MARK_CHIPRESET, chan ? chan->ic_freq : 0);

	/*
	 * Reset the HW - PCI must be reset after the rest of the
	 * device has been reset
	 */
	if (!ar5212SetResetReg(ah, AR_RC_MAC | AR_RC_BB | AR_RC_PCI))
		return AH_FALSE;

	/* Bring out of sleep mode (AGAIN) */
	if (!ar5212SetPowerMode(ah, HAL_PM_AWAKE, AH_TRUE))
		return AH_FALSE;

	/* Clear warm reset register */
	if (!ar5212SetResetReg(ah, 0))
		return AH_FALSE;

	/*
	 * Perform warm reset before the mode/PLL/turbo registers
	 * are changed in order to deactivate the radio.  Mode changes
	 * with an active radio can result in corrupted shifts to the
	 * radio device.
	 */

	/*
	 * Set CCK and Turbo modes correctly.
	 */
	if (chan != AH_NULL) {		/* NB: can be null during attach */
		uint32_t rfMode, phyPLL = 0, curPhyPLL, turbo;

		if (IS_5413(ah)) {	/* NB: =>'s 5424 also */
			rfMode = AR_PHY_MODE_AR5112;
			if (IEEE80211_IS_CHAN_HALF(chan))
				rfMode |= AR_PHY_MODE_HALF;
			else if (IEEE80211_IS_CHAN_QUARTER(chan))
				rfMode |= AR_PHY_MODE_QUARTER;

			if (IEEE80211_IS_CHAN_CCK(chan))
				phyPLL = AR_PHY_PLL_CTL_44_5112;
			else
				phyPLL = AR_PHY_PLL_CTL_40_5413;
		} else if (IS_RAD5111(ah)) {
			rfMode = AR_PHY_MODE_AR5111;
			if (IEEE80211_IS_CHAN_CCK(chan))
				phyPLL = AR_PHY_PLL_CTL_44;
			else
				phyPLL = AR_PHY_PLL_CTL_40;
			if (IEEE80211_IS_CHAN_HALF(chan))
				phyPLL = AR_PHY_PLL_CTL_HALF;
			else if (IEEE80211_IS_CHAN_QUARTER(chan))
				phyPLL = AR_PHY_PLL_CTL_QUARTER;
		} else {		/* 5112, 2413, 2316, 2317 */
			rfMode = AR_PHY_MODE_AR5112;
			if (IEEE80211_IS_CHAN_CCK(chan))
				phyPLL = AR_PHY_PLL_CTL_44_5112;
			else
				phyPLL = AR_PHY_PLL_CTL_40_5112;
			if (IEEE80211_IS_CHAN_HALF(chan))
				phyPLL |= AR_PHY_PLL_CTL_HALF;
			else if (IEEE80211_IS_CHAN_QUARTER(chan))
				phyPLL |= AR_PHY_PLL_CTL_QUARTER;
		}
		if (IEEE80211_IS_CHAN_G(chan))
			rfMode |= AR_PHY_MODE_DYNAMIC;
		else if (IEEE80211_IS_CHAN_OFDM(chan))
			rfMode |= AR_PHY_MODE_OFDM;
		else
			rfMode |= AR_PHY_MODE_CCK;
		if (IEEE80211_IS_CHAN_5GHZ(chan))
			rfMode |= AR_PHY_MODE_RF5GHZ;
		else
			rfMode |= AR_PHY_MODE_RF2GHZ;
		turbo = IEEE80211_IS_CHAN_TURBO(chan) ?
			(AR_PHY_FC_TURBO_MODE | AR_PHY_FC_TURBO_SHORT) : 0;
		curPhyPLL = OS_REG_READ(ah, AR_PHY_PLL_CTL);
		/*
		 * PLL, Mode, and Turbo values must be written in the correct
		 * order to ensure:
		 * - The PLL cannot be set to 44 unless the CCK or DYNAMIC
		 *   mode bit is set
		 * - Turbo cannot be set at the same time as CCK or DYNAMIC
		 */
		if (IEEE80211_IS_CHAN_CCK(chan)) {
			OS_REG_WRITE(ah, AR_PHY_TURBO, turbo);
			OS_REG_WRITE(ah, AR_PHY_MODE, rfMode);
			if (curPhyPLL != phyPLL) {
				OS_REG_WRITE(ah,  AR_PHY_PLL_CTL,  phyPLL);
				/* Wait for the PLL to settle */
				OS_DELAY(PLL_SETTLE_DELAY);
			}
		} else {
			if (curPhyPLL != phyPLL) {
				OS_REG_WRITE(ah,  AR_PHY_PLL_CTL,  phyPLL);
				/* Wait for the PLL to settle */
				OS_DELAY(PLL_SETTLE_DELAY);
			}
			OS_REG_WRITE(ah, AR_PHY_TURBO, turbo);
			OS_REG_WRITE(ah, AR_PHY_MODE, rfMode);
		}
	}
	return AH_TRUE;
}