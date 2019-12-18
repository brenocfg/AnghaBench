#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint16_t ;
struct ieee80211_channel {int dummy; } ;
struct calDataPerFreqOpLoop {scalar_t__** pcdac; scalar_t__** pwrPdg; } ;
struct ath_hal {int dummy; } ;
struct TYPE_5__ {scalar_t__* originalGain; } ;
struct TYPE_4__ {int /*<<< orphan*/  synth_center; } ;
typedef  scalar_t__ HAL_BOOL ;
typedef  TYPE_1__ CHAN_CENTERS ;

/* Variables and functions */
 TYPE_3__* AH9280 (struct ath_hal*) ; 
 scalar_t__ AR5416_BCHAN_UNUSED ; 
 int AR9280_TX_GAIN_TABLE_SIZE ; 
 scalar_t__ FREQ2FBIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  ar5416GetChannelCenters (struct ath_hal*,struct ieee80211_channel const*,TYPE_1__*) ; 
 scalar_t__ ath_ee_getLowerUpperIndex (scalar_t__,scalar_t__*,size_t,size_t*,size_t*) ; 

void
ar9280olcGetTxGainIndex(struct ath_hal *ah,
    const struct ieee80211_channel *chan,
    struct calDataPerFreqOpLoop *rawDatasetOpLoop,
    uint8_t *calChans, uint16_t availPiers, uint8_t *pwr, uint8_t *pcdacIdx)
{
	uint8_t pcdac, i = 0;
	uint16_t idxL = 0, idxR = 0, numPiers;
	HAL_BOOL match;
	CHAN_CENTERS centers;

	ar5416GetChannelCenters(ah, chan, &centers);

	for (numPiers = 0; numPiers < availPiers; numPiers++)
		if (calChans[numPiers] == AR5416_BCHAN_UNUSED)
			break;

	match = ath_ee_getLowerUpperIndex((uint8_t)FREQ2FBIN(centers.synth_center,
		    IEEE80211_IS_CHAN_2GHZ(chan)), calChans, numPiers,
		    &idxL, &idxR);
	if (match) {
		pcdac = rawDatasetOpLoop[idxL].pcdac[0][0];
		*pwr = rawDatasetOpLoop[idxL].pwrPdg[0][0];
	} else {
		pcdac = rawDatasetOpLoop[idxR].pcdac[0][0];
		*pwr = (rawDatasetOpLoop[idxL].pwrPdg[0][0] +
				rawDatasetOpLoop[idxR].pwrPdg[0][0])/2;
	}
	while (pcdac > AH9280(ah)->originalGain[i] &&
			i < (AR9280_TX_GAIN_TABLE_SIZE - 1))
		i++;

	*pcdacIdx = i;
}