#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  freqband; } ;
struct malo_hal_channel {TYPE_1__ flags; int /*<<< orphan*/  channel; } ;
struct ieee80211_channel {int /*<<< orphan*/  ic_ieee; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  MALO_FREQ_BAND_2DOT4GHZ ; 

__attribute__((used)) static void
malo_mapchan(struct malo_hal_channel *hc, const struct ieee80211_channel *chan)
{
	hc->channel = chan->ic_ieee;

	*(uint32_t *)&hc->flags = 0;
	if (IEEE80211_IS_CHAN_2GHZ(chan))
		hc->flags.freqband = MALO_FREQ_BAND_2DOT4GHZ;
}