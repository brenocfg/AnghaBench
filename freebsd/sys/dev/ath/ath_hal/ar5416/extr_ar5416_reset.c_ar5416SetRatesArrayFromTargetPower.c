#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
typedef  scalar_t__ int16_t ;
struct TYPE_10__ {scalar_t__* tPow2x; } ;
struct TYPE_9__ {scalar_t__* tPow2x; } ;
typedef  TYPE_1__ CAL_TARGET_POWER_LEG ;
typedef  TYPE_2__ CAL_TARGET_POWER_HT ;

/* Variables and functions */
 int Ar5416RateSize ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 int N (scalar_t__*) ; 
 size_t rate11l ; 
 size_t rate11s ; 
 size_t rate12mb ; 
 size_t rate18mb ; 
 size_t rate1l ; 
 size_t rate24mb ; 
 size_t rate2l ; 
 size_t rate2s ; 
 size_t rate36mb ; 
 size_t rate48mb ; 
 size_t rate54mb ; 
 size_t rate5_5l ; 
 size_t rate5_5s ; 
 size_t rate6mb ; 
 size_t rate9mb ; 
 size_t rateDupCck ; 
 size_t rateDupOfdm ; 
 size_t rateExtCck ; 
 size_t rateExtOfdm ; 
 int rateHt20_0 ; 
 int rateHt40_0 ; 
 size_t rateXr ; 

void
ar5416SetRatesArrayFromTargetPower(struct ath_hal *ah,
    const struct ieee80211_channel *chan,
    int16_t *ratesArray,
    const CAL_TARGET_POWER_LEG *targetPowerCck,
    const CAL_TARGET_POWER_LEG *targetPowerCckExt,
    const CAL_TARGET_POWER_LEG *targetPowerOfdm,
    const CAL_TARGET_POWER_LEG *targetPowerOfdmExt,
    const CAL_TARGET_POWER_HT *targetPowerHt20,
    const CAL_TARGET_POWER_HT *targetPowerHt40)
{
#define	N(a)	(sizeof(a)/sizeof(a[0]))
	int i;

	/* Blank the rates array, to be consistent */
	for (i = 0; i < Ar5416RateSize; i++)
		ratesArray[i] = 0;

	/* Set rates Array from collected data */
	ratesArray[rate6mb] = ratesArray[rate9mb] = ratesArray[rate12mb] =
	ratesArray[rate18mb] = ratesArray[rate24mb] =
	    targetPowerOfdm->tPow2x[0];
	ratesArray[rate36mb] = targetPowerOfdm->tPow2x[1];
	ratesArray[rate48mb] = targetPowerOfdm->tPow2x[2];
	ratesArray[rate54mb] = targetPowerOfdm->tPow2x[3];
	ratesArray[rateXr] = targetPowerOfdm->tPow2x[0];

	for (i = 0; i < N(targetPowerHt20->tPow2x); i++) {
		ratesArray[rateHt20_0 + i] = targetPowerHt20->tPow2x[i];
	}

	if (IEEE80211_IS_CHAN_2GHZ(chan)) {
		ratesArray[rate1l]  = targetPowerCck->tPow2x[0];
		ratesArray[rate2s] = ratesArray[rate2l]  = targetPowerCck->tPow2x[1];
		ratesArray[rate5_5s] = ratesArray[rate5_5l] = targetPowerCck->tPow2x[2];
		ratesArray[rate11s] = ratesArray[rate11l] = targetPowerCck->tPow2x[3];
	}
	if (IEEE80211_IS_CHAN_HT40(chan)) {
		for (i = 0; i < N(targetPowerHt40->tPow2x); i++) {
			ratesArray[rateHt40_0 + i] = targetPowerHt40->tPow2x[i];
		}
		ratesArray[rateDupOfdm] = targetPowerHt40->tPow2x[0];
		ratesArray[rateDupCck]  = targetPowerHt40->tPow2x[0];
		ratesArray[rateExtOfdm] = targetPowerOfdmExt->tPow2x[0];
		if (IEEE80211_IS_CHAN_2GHZ(chan)) {
			ratesArray[rateExtCck]  = targetPowerCckExt->tPow2x[0];
		}
	}
#undef	N
}