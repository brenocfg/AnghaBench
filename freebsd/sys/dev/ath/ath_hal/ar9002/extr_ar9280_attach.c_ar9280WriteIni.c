#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_7__ {int cols; int rows; } ;
struct TYPE_10__ {TYPE_1__ ah_ini_common; TYPE_1__ ah_ini_modes; } ;
struct TYPE_9__ {scalar_t__ ah_need_an_top2_fixup; } ;
struct TYPE_8__ {TYPE_1__ ah_ini_xmodes; TYPE_1__ ah_ini_txgain; TYPE_1__ ah_ini_rxgain; } ;
typedef  TYPE_1__ HAL_INI_ARRAY ;

/* Variables and functions */
 TYPE_6__* AH5212 (struct ath_hal*) ; 
 TYPE_5__* AH5416 (struct ath_hal*) ; 
 TYPE_4__* AH9280 (struct ath_hal*) ; 
 int AR_AN_TOP2 ; 
 int AR_AN_TOP2_PWDCLKIND ; 
 int AR_PHY (int /*<<< orphan*/ ) ; 
 int AR_PHY_ADC_SERIAL_CTL ; 
 int AR_PHY_SEL_INTERNAL_ADDAC ; 
 scalar_t__ AR_SREV_MERLIN_20 (struct ath_hal*) ; 
 scalar_t__ AR_SREV_MERLIN_20_OR_LATER (struct ath_hal*) ; 
 int /*<<< orphan*/  DMA_YIELD (int) ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int HAL_INI_VAL (TYPE_1__ const*,int,int) ; 
 scalar_t__ IEEE80211_IS_CHAN_108G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel const*) ; 
 scalar_t__ IS_5GHZ_FAST_CLOCK_EN (struct ath_hal*,struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int,int) ; 
 int ath_hal_ini_write (struct ath_hal*,TYPE_1__*,int,int) ; 

__attribute__((used)) static void
ar9280WriteIni(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	u_int modesIndex, freqIndex;
	int regWrites = 0;
	int i;
	const HAL_INI_ARRAY *ia;

	/* Setup the indices for the next set of register array writes */
	/* XXX Ignore 11n dynamic mode on the AR5416 for the moment */
	if (IEEE80211_IS_CHAN_2GHZ(chan)) {
		freqIndex = 2;
		if (IEEE80211_IS_CHAN_HT40(chan))
			modesIndex = 3;
		else if (IEEE80211_IS_CHAN_108G(chan))
			modesIndex = 5;
		else
			modesIndex = 4;
	} else {
		freqIndex = 1;
		if (IEEE80211_IS_CHAN_HT40(chan) ||
		    IEEE80211_IS_CHAN_TURBO(chan))
			modesIndex = 2;
		else
			modesIndex = 1;
	}

	/* Set correct Baseband to analog shift setting to access analog chips. */
	OS_REG_WRITE(ah, AR_PHY(0), 0x00000007);
	OS_REG_WRITE(ah, AR_PHY_ADC_SERIAL_CTL, AR_PHY_SEL_INTERNAL_ADDAC);

	/*
	 * This is unwound because at the moment, there's a requirement
	 * for Merlin (and later, perhaps) to have a specific bit fixed
	 * in the AR_AN_TOP2 register before writing it.
	 */
	ia = &AH5212(ah)->ah_ini_modes;
#if 0
	regWrites = ath_hal_ini_write(ah, &AH5212(ah)->ah_ini_modes,
	    modesIndex, regWrites);
#endif
	HALASSERT(modesIndex < ia->cols);
	for (i = 0; i < ia->rows; i++) {
		uint32_t reg = HAL_INI_VAL(ia, i, 0);
		uint32_t val = HAL_INI_VAL(ia, i, modesIndex);

		if (reg == AR_AN_TOP2 && AH5416(ah)->ah_need_an_top2_fixup)
			val &= ~AR_AN_TOP2_PWDCLKIND;

		OS_REG_WRITE(ah, reg, val);

		/* Analog shift register delay seems needed for Merlin - PR kern/154220 */
		if (reg >= 0x7800 && reg < 0x7900)
			OS_DELAY(100);

		DMA_YIELD(regWrites);
	}

	if (AR_SREV_MERLIN_20_OR_LATER(ah)) {
		regWrites = ath_hal_ini_write(ah, &AH9280(ah)->ah_ini_rxgain,
		    modesIndex, regWrites);
		regWrites = ath_hal_ini_write(ah, &AH9280(ah)->ah_ini_txgain,
		    modesIndex, regWrites);
	}
	/* XXX Merlin 100us delay for shift registers */
	regWrites = ath_hal_ini_write(ah, &AH5212(ah)->ah_ini_common,
	    1, regWrites);

	if (AR_SREV_MERLIN_20(ah) && IS_5GHZ_FAST_CLOCK_EN(ah, chan)) {
		/* 5GHz channels w/ Fast Clock use different modal values */
		regWrites = ath_hal_ini_write(ah, &AH9280(ah)->ah_ini_xmodes,
		    modesIndex, regWrites);
	}
}