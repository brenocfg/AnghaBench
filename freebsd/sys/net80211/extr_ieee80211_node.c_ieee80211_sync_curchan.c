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
struct ieee80211com {int /*<<< orphan*/  (* ic_set_channel ) (struct ieee80211com*) ;struct ieee80211_channel* ic_curchan; int /*<<< orphan*/  ic_rt; int /*<<< orphan*/  ic_curmode; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  gethtadjustflags (struct ieee80211com*) ; 
 int /*<<< orphan*/  getvhtadjustflags (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_chan2mode (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ieee80211_get_ratetable (struct ieee80211_channel*) ; 
 struct ieee80211_channel* ieee80211_ht_adjust_channel (struct ieee80211com*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_radiotap_chan_change (struct ieee80211com*) ; 
 struct ieee80211_channel* ieee80211_vht_adjust_channel (struct ieee80211com*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211com*) ; 

void
ieee80211_sync_curchan(struct ieee80211com *ic)
{
	struct ieee80211_channel *c;

	c = ieee80211_ht_adjust_channel(ic, ic->ic_curchan, gethtadjustflags(ic));
	c = ieee80211_vht_adjust_channel(ic, c, getvhtadjustflags(ic));

	if (c != ic->ic_curchan) {
		ic->ic_curchan = c;
		ic->ic_curmode = ieee80211_chan2mode(ic->ic_curchan);
		ic->ic_rt = ieee80211_get_ratetable(ic->ic_curchan);
		IEEE80211_UNLOCK(ic);
		ic->ic_set_channel(ic);
		ieee80211_radiotap_chan_change(ic);
		IEEE80211_LOCK(ic);
	}
}