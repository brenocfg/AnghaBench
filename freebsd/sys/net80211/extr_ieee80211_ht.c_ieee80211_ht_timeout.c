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
struct ieee80211com {int ic_flags_ht; scalar_t__ ic_lastnonht; } ;

/* Variables and functions */
 int IEEE80211_FHT_NONHT_PR ; 
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_MSG_11N ; 
 scalar_t__ IEEE80211_NONHT_PRESENT_AGE ; 
 int /*<<< orphan*/  IEEE80211_NOTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  htinfo_update (struct ieee80211com*) ; 
 scalar_t__ ieee80211_time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ni ; 
 int /*<<< orphan*/  ticks ; 
 int /*<<< orphan*/  vap ; 

void
ieee80211_ht_timeout(struct ieee80211com *ic)
{
	IEEE80211_LOCK_ASSERT(ic);

	if ((ic->ic_flags_ht & IEEE80211_FHT_NONHT_PR) &&
	    ieee80211_time_after(ticks, ic->ic_lastnonht + IEEE80211_NONHT_PRESENT_AGE)) {
#if 0
		IEEE80211_NOTE(vap, IEEE80211_MSG_11N, ni,
		    "%s", "time out non-HT STA present on channel");
#endif
		ic->ic_flags_ht &= ~IEEE80211_FHT_NONHT_PR;
		htinfo_update(ic);
	}
}