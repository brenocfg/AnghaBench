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
struct ieee80211vap {scalar_t__ iv_des_mode; int /*<<< orphan*/  iv_ic; } ;
struct ieee80211_channel {int ic_flags; int /*<<< orphan*/  ic_freq; } ;

/* Variables and functions */
 int IEEE80211_CHAN_B ; 
 int IEEE80211_CHAN_G ; 
 int IEEE80211_CHAN_PUREG ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_MODE_AUTO ; 
 struct ieee80211_channel* ieee80211_find_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ieee80211_channel *
demote11b(struct ieee80211vap *vap, struct ieee80211_channel *chan)
{
	struct ieee80211_channel *c;

	if (IEEE80211_IS_CHAN_ANYG(chan) &&
	    vap->iv_des_mode == IEEE80211_MODE_AUTO) {
		c = ieee80211_find_channel(vap->iv_ic, chan->ic_freq,
		    (chan->ic_flags &~ (IEEE80211_CHAN_PUREG | IEEE80211_CHAN_G)) |
		    IEEE80211_CHAN_B);
		if (c != NULL)
			chan = c;
	}
	return chan;
}