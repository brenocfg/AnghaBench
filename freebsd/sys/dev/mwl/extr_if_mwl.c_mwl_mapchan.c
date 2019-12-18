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
typedef  scalar_t__ uint32_t ;
struct ieee80211_channel {int /*<<< orphan*/  ic_ieee; } ;
struct TYPE_4__ {int /*<<< orphan*/  ChnlWidth; int /*<<< orphan*/  ExtChnlOffset; int /*<<< orphan*/  FreqBand; } ;
struct TYPE_5__ {TYPE_1__ channelFlags; int /*<<< orphan*/  channel; } ;
typedef  TYPE_2__ MWL_HAL_CHANNEL ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel const*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40U (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  MWL_CH_20_MHz_WIDTH ; 
 int /*<<< orphan*/  MWL_CH_40_MHz_WIDTH ; 
 int /*<<< orphan*/  MWL_EXT_CH_ABOVE_CTRL_CH ; 
 int /*<<< orphan*/  MWL_EXT_CH_BELOW_CTRL_CH ; 
 int /*<<< orphan*/  MWL_FREQ_BAND_2DOT4GHZ ; 
 int /*<<< orphan*/  MWL_FREQ_BAND_5GHZ ; 

__attribute__((used)) static void
mwl_mapchan(MWL_HAL_CHANNEL *hc, const struct ieee80211_channel *chan)
{
	hc->channel = chan->ic_ieee;

	*(uint32_t *)&hc->channelFlags = 0;
	if (IEEE80211_IS_CHAN_2GHZ(chan))
		hc->channelFlags.FreqBand = MWL_FREQ_BAND_2DOT4GHZ;
	else if (IEEE80211_IS_CHAN_5GHZ(chan))
		hc->channelFlags.FreqBand = MWL_FREQ_BAND_5GHZ;
	if (IEEE80211_IS_CHAN_HT40(chan)) {
		hc->channelFlags.ChnlWidth = MWL_CH_40_MHz_WIDTH;
		if (IEEE80211_IS_CHAN_HT40U(chan))
			hc->channelFlags.ExtChnlOffset = MWL_EXT_CH_ABOVE_CTRL_CH;
		else
			hc->channelFlags.ExtChnlOffset = MWL_EXT_CH_BELOW_CTRL_CH;
	} else
		hc->channelFlags.ChnlWidth = MWL_CH_20_MHz_WIDTH;
	/* XXX 10MHz channels */
}