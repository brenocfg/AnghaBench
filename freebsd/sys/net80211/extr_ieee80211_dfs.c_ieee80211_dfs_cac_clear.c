#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ieee80211com {int ic_nchans; struct ieee80211_channel* ic_channels; } ;
struct ieee80211_channel {scalar_t__ ic_freq; int /*<<< orphan*/  ic_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHANSTATE_CACDONE ; 

void
ieee80211_dfs_cac_clear(struct ieee80211com *ic,
	const struct ieee80211_channel *chan)
{
	int i;

	for (i = 0; i < ic->ic_nchans; i++) {
		struct ieee80211_channel *c = &ic->ic_channels[i];
		if (c->ic_freq == chan->ic_freq)
			c->ic_state &= ~IEEE80211_CHANSTATE_CACDONE;
	}
}