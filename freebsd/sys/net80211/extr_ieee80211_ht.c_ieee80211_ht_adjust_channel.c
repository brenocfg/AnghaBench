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
struct ieee80211com {int dummy; } ;
struct ieee80211_channel {int ic_flags; int /*<<< orphan*/  ic_freq; } ;

/* Variables and functions */
 int IEEE80211_CHAN_HT ; 
 int /*<<< orphan*/  IEEE80211_CHAN_HT20 ; 
 int /*<<< orphan*/  IEEE80211_CHAN_HT40D ; 
 int /*<<< orphan*/  IEEE80211_CHAN_HT40U ; 
 int IEEE80211_FHT_HT ; 
 int IEEE80211_FHT_USEHT40 ; 
 scalar_t__ IEEE80211_IS_CHAN_HT (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_HT20 (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel*) ; 
 struct ieee80211_channel* findhtchan (struct ieee80211com*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 struct ieee80211_channel* ieee80211_find_channel (struct ieee80211com*,int /*<<< orphan*/ ,int) ; 

struct ieee80211_channel *
ieee80211_ht_adjust_channel(struct ieee80211com *ic,
	struct ieee80211_channel *chan, int flags)
{
	struct ieee80211_channel *c;

	if (flags & IEEE80211_FHT_HT) {
		/* promote to HT if possible */
		if (flags & IEEE80211_FHT_USEHT40) {
			if (!IEEE80211_IS_CHAN_HT40(chan)) {
				/* NB: arbitrarily pick ht40+ over ht40- */
				c = findhtchan(ic, chan, IEEE80211_CHAN_HT40U);
				if (c == NULL)
					c = findhtchan(ic, chan,
						IEEE80211_CHAN_HT40D);
				if (c == NULL)
					c = findhtchan(ic, chan,
						IEEE80211_CHAN_HT20);
				if (c != NULL)
					chan = c;
			}
		} else if (!IEEE80211_IS_CHAN_HT20(chan)) {
			c = findhtchan(ic, chan, IEEE80211_CHAN_HT20);
			if (c != NULL)
				chan = c;
		}
	} else if (IEEE80211_IS_CHAN_HT(chan)) {
		/* demote to legacy, HT use is disabled */
		c = ieee80211_find_channel(ic, chan->ic_freq,
		    chan->ic_flags &~ IEEE80211_CHAN_HT);
		if (c != NULL)
			chan = c;
	}
	return chan;
}