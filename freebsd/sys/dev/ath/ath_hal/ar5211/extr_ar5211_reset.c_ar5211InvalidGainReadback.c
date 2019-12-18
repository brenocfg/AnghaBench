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
typedef  int uint32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_5__ {struct ieee80211_channel* ah_curchan; } ;
struct TYPE_4__ {int loTrig; int hiTrig; int currGain; } ;
typedef  int HAL_BOOL ;
typedef  TYPE_1__ GAIN_VALUES ;

/* Variables and functions */
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int DYN_ADJ_LO_MARGIN ; 
 int DYN_ADJ_UP_MARGIN ; 
 scalar_t__ IEEE80211_IS_CHAN_CCK (struct ieee80211_channel const*) ; 

__attribute__((used)) static HAL_BOOL
ar5211InvalidGainReadback(struct ath_hal *ah, GAIN_VALUES *gv)
{
	const struct ieee80211_channel *chan = AH_PRIVATE(ah)->ah_curchan;
	uint32_t gStep, g;
	uint32_t L1, L2, L3, L4;

	if (IEEE80211_IS_CHAN_CCK(chan)) {
		gStep = 0x18;
		L1 = 0;
		L2 = gStep + 4;
		L3 = 0x40;
		L4 = L3 + 50;

		gv->loTrig = L1;
		gv->hiTrig = L4+5;
	} else {
		gStep = 0x3f;
		L1 = 0;
		L2 = 50;
		L3 = L1;
		L4 = L3 + 50;

		gv->loTrig = L1 + DYN_ADJ_LO_MARGIN;
		gv->hiTrig = L4 - DYN_ADJ_UP_MARGIN;
	}
	g = gv->currGain;

	return !((g >= L1 && g<= L2) || (g >= L3 && g <= L4));
}