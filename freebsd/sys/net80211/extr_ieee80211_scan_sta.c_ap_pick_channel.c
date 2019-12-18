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
struct sta_table {scalar_t__* st_maxrssi; } ;
struct ieee80211_scan_state {int ss_last; struct ieee80211_channel** ss_chans; struct sta_table* ss_priv; } ;
struct ieee80211_channel {int ic_flags; size_t ic_ieee; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_NOHOSTAP (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_RADAR (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static struct ieee80211_channel *
ap_pick_channel(struct ieee80211_scan_state *ss, int flags)
{
	struct sta_table *st = ss->ss_priv;
	struct ieee80211_channel *bestchan = NULL;
	int i;

	/* XXX select channel more intelligently, e.g. channel spread, power */
	/* NB: use scan list order to preserve channel preference */
	for (i = 0; i < ss->ss_last; i++) {
		struct ieee80211_channel *chan = ss->ss_chans[i];
		/*
		 * If the channel is unoccupied the max rssi
		 * should be zero; just take it.  Otherwise
		 * track the channel with the lowest rssi and
		 * use that when all channels appear occupied.
		 */
		if (IEEE80211_IS_CHAN_RADAR(chan))
			continue;
		if (IEEE80211_IS_CHAN_NOHOSTAP(chan))
			continue;
		/* check channel attributes for band compatibility */
		if (flags != 0 && (chan->ic_flags & flags) != flags)
			continue;
		KASSERT(sizeof(chan->ic_ieee) == 1, ("ic_chan size"));
		/* XXX channel have interference */
		if (st->st_maxrssi[chan->ic_ieee] == 0) {
			/* XXX use other considerations */
			return chan;
		}
		if (bestchan == NULL ||
		    st->st_maxrssi[chan->ic_ieee] < st->st_maxrssi[bestchan->ic_ieee])
			bestchan = chan;
	}
	return bestchan;
}