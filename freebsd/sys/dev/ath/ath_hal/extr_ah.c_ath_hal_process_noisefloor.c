#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
typedef  scalar_t__ int16_t ;
typedef  size_t WIRELESS_MODE ;
struct TYPE_6__ {int ah_nchan; TYPE_1__* ah_channels; } ;
struct TYPE_5__ {scalar_t__ rawNoiseFloor; scalar_t__ noiseFloorAdjust; int /*<<< orphan*/  channel; } ;
typedef  TYPE_1__ HAL_CHANNEL_INTERNAL ;

/* Variables and functions */
 TYPE_4__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HAL_DEBUG_NFCAL ; 
 scalar_t__ IS_CHAN_5GHZ (TYPE_1__*) ; 
 scalar_t__* NOISE_FLOOR ; 
 size_t WIRELESS_MODE_11a ; 
 size_t WIRELESS_MODE_11g ; 
 scalar_t__ ath_hal_getNfAdjust (struct ath_hal*,TYPE_1__*) ; 

void
ath_hal_process_noisefloor(struct ath_hal *ah)
{
	HAL_CHANNEL_INTERNAL *c;
	int16_t correct2, correct5;
	int16_t lowest2, lowest5;
	int i;

	/* 
	 * Find the lowest 2GHz and 5GHz noise floor values after adjusting
	 * for statistically recorded NF/channel deviation.
	 */
	correct2 = lowest2 = 0;
	correct5 = lowest5 = 0;
	for (i = 0; i < AH_PRIVATE(ah)->ah_nchan; i++) {
		WIRELESS_MODE mode;
		int16_t nf;

		c = &AH_PRIVATE(ah)->ah_channels[i];
		if (c->rawNoiseFloor >= 0)
			continue;
		/* XXX can't identify proper mode */
		mode = IS_CHAN_5GHZ(c) ? WIRELESS_MODE_11a : WIRELESS_MODE_11g;
		nf = c->rawNoiseFloor + NOISE_FLOOR[mode] +
			ath_hal_getNfAdjust(ah, c);
		if (IS_CHAN_5GHZ(c)) {
			if (nf < lowest5) { 
				lowest5 = nf;
				correct5 = NOISE_FLOOR[mode] -
				    (c->rawNoiseFloor + ath_hal_getNfAdjust(ah, c));
			}
		} else {
			if (nf < lowest2) { 
				lowest2 = nf;
				correct2 = NOISE_FLOOR[mode] -
				    (c->rawNoiseFloor + ath_hal_getNfAdjust(ah, c));
			}
		}
	}

	/* Correct the channels to reach the expected NF value */
	for (i = 0; i < AH_PRIVATE(ah)->ah_nchan; i++) {
		c = &AH_PRIVATE(ah)->ah_channels[i];
		if (c->rawNoiseFloor >= 0)
			continue;
		/* Apply correction factor */
		c->noiseFloorAdjust = ath_hal_getNfAdjust(ah, c) +
			(IS_CHAN_5GHZ(c) ? correct5 : correct2);
		HALDEBUG(ah, HAL_DEBUG_NFCAL, "%u raw nf %d adjust %d\n",
		    c->channel, c->rawNoiseFloor, c->noiseFloorAdjust);
	}
}