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
struct ieee80211com {int ic_htcaps; scalar_t__ ic_vhtcaps; struct ieee80211_channel* ic_curchan; int /*<<< orphan*/  ic_rt; int /*<<< orphan*/  ic_curmode; struct ieee80211_channel* ic_bsschan; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int IEEE80211_HTC_HT ; 
 int gethtadjustflags (struct ieee80211com*) ; 
 int getvhtadjustflags (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_chan2mode (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ieee80211_get_ratetable (struct ieee80211_channel*) ; 
 struct ieee80211_channel* ieee80211_ht_adjust_channel (struct ieee80211com*,struct ieee80211_channel*,int) ; 
 int ieee80211_htchanflags (struct ieee80211_channel*) ; 
 struct ieee80211_channel* ieee80211_vht_adjust_channel (struct ieee80211com*,struct ieee80211_channel*,int) ; 
 int ieee80211_vhtchanflags (struct ieee80211_channel*) ; 

void
ieee80211_setupcurchan(struct ieee80211com *ic, struct ieee80211_channel *c)
{
	if (ic->ic_htcaps & IEEE80211_HTC_HT) {
		int flags = gethtadjustflags(ic);
		/*
		 * Check for channel promotion required to support the
		 * set of running vap's.  This assumes we are called
		 * after ni_chan is setup for each vap.
		 */
		/* XXX VHT? */
		/* NB: this assumes IEEE80211_FHT_USEHT40 > IEEE80211_FHT_HT */
		if (flags > ieee80211_htchanflags(c))
			c = ieee80211_ht_adjust_channel(ic, c, flags);
	}

	/*
	 * VHT promotion - this will at least promote to VHT20/40
	 * based on what HT has done; it may further promote the
	 * channel to VHT80 or above.
	 */
	if (ic->ic_vhtcaps != 0) {
		int flags = getvhtadjustflags(ic);
		if (flags > ieee80211_vhtchanflags(c))
			c = ieee80211_vht_adjust_channel(ic, c, flags);
	}

	ic->ic_bsschan = ic->ic_curchan = c;
	ic->ic_curmode = ieee80211_chan2mode(ic->ic_curchan);
	ic->ic_rt = ieee80211_get_ratetable(ic->ic_curchan);
}