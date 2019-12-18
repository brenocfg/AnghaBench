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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct ieee80211_channel {scalar_t__ ic_freq; int ic_flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_ALLTURBO ; 

__attribute__((used)) static struct ieee80211_channel *
findchannel(struct ieee80211_channel chans[], int nchans, uint16_t freq,
    uint32_t flags)
{
	struct ieee80211_channel *c;
	int i;

	flags &= IEEE80211_CHAN_ALLTURBO;
	/* brute force search */
	for (i = 0; i < nchans; i++) {
		c = &chans[i];
		if (c->ic_freq == freq &&
		    (c->ic_flags & IEEE80211_CHAN_ALLTURBO) == flags)
			return c;
	}
	return NULL;
}