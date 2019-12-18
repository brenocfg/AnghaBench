#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {scalar_t__ channel; } ;
struct ath_hal_5212 {TYPE_2__* ah_modePowerArray5112; } ;
struct ath_hal {int dummy; } ;
typedef  int int8_t ;
typedef  int int16_t ;
struct TYPE_5__ {int numChannels; TYPE_1__* pDataPerChannel; } ;
struct TYPE_4__ {scalar_t__ channelValue; int maxPower_t4; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  TYPE_1__ EXPN_DATA_PER_CHANNEL_5112 ;
typedef  TYPE_2__ EEPROM_POWER_EXPN_5112 ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 void* AH_NULL ; 
 int /*<<< orphan*/  AH_TRUE ; 
 scalar_t__ IS_CHAN_108G (struct ieee80211_channel const*) ; 
 scalar_t__ IS_CHAN_A (struct ieee80211_channel const*) ; 
 scalar_t__ IS_CHAN_B (struct ieee80211_channel const*) ; 
 scalar_t__ IS_CHAN_G (struct ieee80211_channel const*) ; 
 int ar2133GetMinPower (struct ath_hal*,TYPE_1__*) ; 
 size_t headerInfo11A ; 
 size_t headerInfo11B ; 
 size_t headerInfo11G ; 

__attribute__((used)) static HAL_BOOL
ar2133GetChannelMaxMinPower(struct ath_hal *ah,
	const struct ieee80211_channel *chan,
	int16_t *maxPow, int16_t *minPow)
{
#if 0
    struct ath_hal_5212 *ahp = AH5212(ah);
    int numChannels=0,i,last;
    int totalD, totalF,totalMin;
    EXPN_DATA_PER_CHANNEL_5112 *data=AH_NULL;
    EEPROM_POWER_EXPN_5112 *powerArray=AH_NULL;

    *maxPow = 0;
    if (IS_CHAN_A(chan)) {
        powerArray = ahp->ah_modePowerArray5112;
        data = powerArray[headerInfo11A].pDataPerChannel;
        numChannels = powerArray[headerInfo11A].numChannels;
    } else if (IS_CHAN_G(chan) || IS_CHAN_108G(chan)) {
        /* XXX - is this correct? Should we also use the same power for turbo G? */
        powerArray = ahp->ah_modePowerArray5112;
        data = powerArray[headerInfo11G].pDataPerChannel;
        numChannels = powerArray[headerInfo11G].numChannels;
    } else if (IS_CHAN_B(chan)) {
        powerArray = ahp->ah_modePowerArray5112;
        data = powerArray[headerInfo11B].pDataPerChannel;
        numChannels = powerArray[headerInfo11B].numChannels;
    } else {
        return (AH_TRUE);
    }
    /* Make sure the channel is in the range of the TP values
     *  (freq piers)
     */
    if ((numChannels < 1) ||
        (chan->channel < data[0].channelValue) ||
        (chan->channel > data[numChannels-1].channelValue))
        return(AH_FALSE);

    /* Linearly interpolate the power value now */
    for (last=0,i=0;
         (i<numChannels) && (chan->channel > data[i].channelValue);
         last=i++);
    totalD = data[i].channelValue - data[last].channelValue;
    if (totalD > 0) {
        totalF = data[i].maxPower_t4 - data[last].maxPower_t4;
        *maxPow = (int8_t) ((totalF*(chan->channel-data[last].channelValue) + data[last].maxPower_t4*totalD)/totalD);

        totalMin = ar2133GetMinPower(ah,&data[i]) - ar2133GetMinPower(ah, &data[last]);
        *minPow = (int8_t) ((totalMin*(chan->channel-data[last].channelValue) + ar2133GetMinPower(ah, &data[last])*totalD)/totalD);
        return (AH_TRUE);
    } else {
        if (chan->channel == data[i].channelValue) {
            *maxPow = data[i].maxPower_t4;
            *minPow = ar2133GetMinPower(ah, &data[i]);
            return(AH_TRUE);
        } else
            return(AH_FALSE);
    }
#else
    *maxPow = *minPow = 0;
	return AH_FALSE;
#endif
}