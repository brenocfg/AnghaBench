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
struct ieee80211_channel {int ic_freq; int ic_flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_ALLTURBO ; 

__attribute__((used)) static const struct ieee80211_channel *
chanlookup(const struct ieee80211_channel chans[], int nchans,
	int freq, int flags)
{
	int i;

	flags &= IEEE80211_CHAN_ALLTURBO;
	for (i = 0; i < nchans; i++) {
		const struct ieee80211_channel *c = &chans[i];
		if (c->ic_freq == freq &&
		    (c->ic_flags & IEEE80211_CHAN_ALLTURBO) == flags)
			return c;
	}
	return NULL;
}