#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct ieee80211_channel {scalar_t__ ic_freq; } ;
struct ath_hal {int dummy; } ;
typedef  int int8_t ;
typedef  int int16_t ;
struct TYPE_9__ {TYPE_1__* ah_eeprom; } ;
struct TYPE_8__ {int numChannels; TYPE_2__* pDataPerChannel; } ;
struct TYPE_7__ {scalar_t__ channelValue; int maxPower_t4; } ;
struct TYPE_6__ {TYPE_3__* ee_modePowerArray5112; } ;
typedef  TYPE_1__ HAL_EEPROM ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  TYPE_2__ EXPN_DATA_PER_CHANNEL_5112 ;
typedef  TYPE_3__ EEPROM_POWER_EXPN_5112 ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 void* AH_NULL ; 
 TYPE_5__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 scalar_t__ IEEE80211_IS_CHAN_108G (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_A (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_B (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_G (struct ieee80211_channel const*) ; 
 int ar5112GetMinPower (struct ath_hal*,TYPE_2__ const*) ; 
 size_t headerInfo11A ; 
 size_t headerInfo11B ; 
 size_t headerInfo11G ; 

__attribute__((used)) static HAL_BOOL
ar5112GetChannelMaxMinPower(struct ath_hal *ah,
	const struct ieee80211_channel *chan,
	int16_t *maxPow, int16_t *minPow)
{
	uint16_t freq = chan->ic_freq;		/* NB: never mapped */
	const HAL_EEPROM *ee = AH_PRIVATE(ah)->ah_eeprom;
	int numChannels=0,i,last;
	int totalD, totalF,totalMin;
	const EXPN_DATA_PER_CHANNEL_5112 *data=AH_NULL;
	const EEPROM_POWER_EXPN_5112 *powerArray=AH_NULL;

	*maxPow = 0;
	if (IEEE80211_IS_CHAN_A(chan)) {
		powerArray = ee->ee_modePowerArray5112;
		data = powerArray[headerInfo11A].pDataPerChannel;
		numChannels = powerArray[headerInfo11A].numChannels;
	} else if (IEEE80211_IS_CHAN_G(chan) || IEEE80211_IS_CHAN_108G(chan)) {
		/* XXX - is this correct? Should we also use the same power for turbo G? */
		powerArray = ee->ee_modePowerArray5112;
		data = powerArray[headerInfo11G].pDataPerChannel;
		numChannels = powerArray[headerInfo11G].numChannels;
	} else if (IEEE80211_IS_CHAN_B(chan)) {
		powerArray = ee->ee_modePowerArray5112;
		data = powerArray[headerInfo11B].pDataPerChannel;
		numChannels = powerArray[headerInfo11B].numChannels;
	} else {
		return (AH_TRUE);
	}
	/* Make sure the channel is in the range of the TP values 
	 *  (freq piers)
	 */
	if (numChannels < 1)
		return(AH_FALSE);

	if ((freq < data[0].channelValue) ||
	    (freq > data[numChannels-1].channelValue)) {
		if (freq < data[0].channelValue) {
			*maxPow = data[0].maxPower_t4;
			*minPow = ar5112GetMinPower(ah, &data[0]);
			return(AH_TRUE);
		} else {
			*maxPow = data[numChannels - 1].maxPower_t4;
			*minPow = ar5112GetMinPower(ah, &data[numChannels - 1]);
			return(AH_TRUE);
		}
	}

	/* Linearly interpolate the power value now */
	for (last=0,i=0;
	     (i<numChannels) && (freq > data[i].channelValue);
	     last=i++);
	totalD = data[i].channelValue - data[last].channelValue;
	if (totalD > 0) {
		totalF = data[i].maxPower_t4 - data[last].maxPower_t4;
		*maxPow = (int8_t) ((totalF*(freq-data[last].channelValue) + data[last].maxPower_t4*totalD)/totalD);

		totalMin = ar5112GetMinPower(ah,&data[i]) - ar5112GetMinPower(ah, &data[last]);
		*minPow = (int8_t) ((totalMin*(freq-data[last].channelValue) + ar5112GetMinPower(ah, &data[last])*totalD)/totalD);
		return (AH_TRUE);
	} else {
		if (freq == data[i].channelValue) {
			*maxPow = data[i].maxPower_t4;
			*minPow = ar5112GetMinPower(ah, &data[i]);
			return(AH_TRUE);
		} else
			return(AH_FALSE);
	}
}