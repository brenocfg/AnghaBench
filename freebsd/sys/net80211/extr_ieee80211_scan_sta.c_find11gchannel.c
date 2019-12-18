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
struct ieee80211_channel {int ic_freq; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_G (struct ieee80211_channel*) ; 

__attribute__((used)) static struct ieee80211_channel *
find11gchannel(struct ieee80211com *ic, int i, int freq)
{
	struct ieee80211_channel *c;
	int j;

	/*
	 * The normal ordering in the channel list is b channel
	 * immediately followed by g so optimize the search for
	 * this.  We'll still do a full search just in case.
	 */
	for (j = i+1; j < ic->ic_nchans; j++) {
		c = &ic->ic_channels[j];
		if (c->ic_freq == freq && IEEE80211_IS_CHAN_G(c))
			return c;
	}
	for (j = 0; j < i; j++) {
		c = &ic->ic_channels[j];
		if (c->ic_freq == freq && IEEE80211_IS_CHAN_G(c))
			return c;
	}
	return NULL;
}