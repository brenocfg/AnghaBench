#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int synth_center; } ;
typedef  TYPE_1__ CHAN_CENTERS ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_HALFGI ; 
 int /*<<< orphan*/  AR_PHY_HALFGI_DSC_EXP ; 
 int /*<<< orphan*/  AR_PHY_HALFGI_DSC_MAN ; 
 int /*<<< orphan*/  AR_PHY_TIMING3 ; 
 int /*<<< orphan*/  AR_PHY_TIMING3_DSC_EXP ; 
 int /*<<< orphan*/  AR_PHY_TIMING3_DSC_MAN ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_TURBO (struct ieee80211_channel const*) ; 
 int INIT_CLOCKMHZSCALED ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5416GetChannelCenters (struct ath_hal*,struct ieee80211_channel const*,TYPE_1__*) ; 
 int /*<<< orphan*/  ar5416GetDeltaSlopeValues (struct ath_hal*,int,int*,int*) ; 

void
ar5416SetDeltaSlope(struct ath_hal *ah, const struct ieee80211_channel *chan)
{
#define INIT_CLOCKMHZSCALED	0x64000000
	uint32_t coef_scaled, ds_coef_exp, ds_coef_man;
	uint32_t clockMhzScaled;

	CHAN_CENTERS centers;

	/* half and quarter rate can divide the scaled clock by 2 or 4 respectively */
	/* scale for selected channel bandwidth */ 
	clockMhzScaled = INIT_CLOCKMHZSCALED;
	if (IEEE80211_IS_CHAN_TURBO(chan))
		clockMhzScaled <<= 1;
	else if (IEEE80211_IS_CHAN_HALF(chan))
		clockMhzScaled >>= 1;
	else if (IEEE80211_IS_CHAN_QUARTER(chan))
		clockMhzScaled >>= 2;

	/*
	 * ALGO -> coef = 1e8/fcarrier*fclock/40;
	 * scaled coef to provide precision for this floating calculation 
	 */
	ar5416GetChannelCenters(ah, chan, &centers);
	coef_scaled = clockMhzScaled / centers.synth_center;		

 	ar5416GetDeltaSlopeValues(ah, coef_scaled, &ds_coef_man, &ds_coef_exp);

	OS_REG_RMW_FIELD(ah, AR_PHY_TIMING3,
		AR_PHY_TIMING3_DSC_MAN, ds_coef_man);
	OS_REG_RMW_FIELD(ah, AR_PHY_TIMING3,
		AR_PHY_TIMING3_DSC_EXP, ds_coef_exp);

        /*
         * For Short GI,
         * scaled coeff is 9/10 that of normal coeff
         */ 
        coef_scaled = (9 * coef_scaled)/10;

        ar5416GetDeltaSlopeValues(ah, coef_scaled, &ds_coef_man, &ds_coef_exp);

        /* for short gi */
        OS_REG_RMW_FIELD(ah, AR_PHY_HALFGI,
                AR_PHY_HALFGI_DSC_MAN, ds_coef_man);
        OS_REG_RMW_FIELD(ah, AR_PHY_HALFGI,
                AR_PHY_HALFGI_DSC_EXP, ds_coef_exp);	
#undef INIT_CLOCKMHZSCALED
}