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
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ah_ini_common; int /*<<< orphan*/  ah_ini_modes; } ;
struct TYPE_3__ {int /*<<< orphan*/  ah_ini_txgain; } ;

/* Variables and functions */
 TYPE_2__* AH5212 (struct ath_hal*) ; 
 TYPE_1__* AH9285 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_PHY_ADC_SERIAL_CTL ; 
 int AR_PHY_SEL_INTERNAL_ADDAC ; 
 scalar_t__ AR_SREV_KITE_12_OR_LATER (struct ath_hal*) ; 
 scalar_t__ IEEE80211_IS_CHAN_108G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int ath_hal_ini_write (struct ath_hal*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
ar9285WriteIni(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
	u_int modesIndex, freqIndex;
	int regWrites = 0;

	/* Setup the indices for the next set of register array writes */
	/* XXX Ignore 11n dynamic mode on the AR5416 for the moment */
	freqIndex = 2;
	if (IEEE80211_IS_CHAN_HT40(chan))
		modesIndex = 3;
	else if (IEEE80211_IS_CHAN_108G(chan))
		modesIndex = 5;
	else
		modesIndex = 4;

	/* Set correct Baseband to analog shift setting to access analog chips. */
	OS_REG_WRITE(ah, AR_PHY(0), 0x00000007);
	OS_REG_WRITE(ah, AR_PHY_ADC_SERIAL_CTL, AR_PHY_SEL_INTERNAL_ADDAC);
	regWrites = ath_hal_ini_write(ah, &AH5212(ah)->ah_ini_modes,
	    modesIndex, regWrites);
	if (AR_SREV_KITE_12_OR_LATER(ah)) {
		regWrites = ath_hal_ini_write(ah, &AH9285(ah)->ah_ini_txgain,
		    modesIndex, regWrites);
	}
	regWrites = ath_hal_ini_write(ah, &AH5212(ah)->ah_ini_common,
	    1, regWrites);
}