#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  survey ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  anistats ;
struct TYPE_8__ {int /*<<< orphan*/  rxframecnt_diff; int /*<<< orphan*/  rx_busy; int /*<<< orphan*/  txframecnt_diff; int /*<<< orphan*/  tx_busy; int /*<<< orphan*/  extrxclr_cnt; int /*<<< orphan*/  ext_chan_busy; int /*<<< orphan*/  rxclr_cnt; int /*<<< orphan*/  chan_busy; int /*<<< orphan*/  cyclecnt_diff; int /*<<< orphan*/  cycle_count; scalar_t__ valid; } ;
typedef  TYPE_1__ HAL_SURVEY_SAMPLE ;
typedef  TYPE_1__ HAL_NODE_STATS ;
typedef  TYPE_1__ HAL_ANISTATS ;

/* Variables and functions */
 int /*<<< orphan*/  OS_MEMZERO (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ar9300_ani_ar_poll (struct ath_hal*,TYPE_1__*,struct ieee80211_channel const*,TYPE_1__*) ; 
 int /*<<< orphan*/  ath_hal_survey_add_sample (struct ath_hal*,TYPE_1__*) ; 

void
ar9300_ani_poll_freebsd(struct ath_hal *ah,
    const struct ieee80211_channel *chan)
{

	HAL_NODE_STATS stats;
	HAL_ANISTATS anistats;
	HAL_SURVEY_SAMPLE survey;

	OS_MEMZERO(&stats, sizeof(stats));
	OS_MEMZERO(&anistats, sizeof(anistats));
	OS_MEMZERO(&survey, sizeof(survey));

	ar9300_ani_ar_poll(ah, &stats, chan, &anistats);

	/*
	 * If ANI stats are valid, use them to update the
	 * channel survey.
	 */
	if (anistats.valid) {
		survey.cycle_count = anistats.cyclecnt_diff;
		survey.chan_busy = anistats.rxclr_cnt;
		survey.ext_chan_busy = anistats.extrxclr_cnt;
		survey.tx_busy = anistats.txframecnt_diff;
		survey.rx_busy = anistats.rxframecnt_diff;
		ath_hal_survey_add_sample(ah, &survey);
	}
}