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
struct ieee80211com {int ic_flags; int /*<<< orphan*/  ic_inact; int /*<<< orphan*/  ic_stageq; } ;

/* Variables and functions */
 int IEEE80211_F_CSAPENDING ; 
 int IEEE80211_INACT_WAIT ; 
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct ieee80211com*) ; 
 int hz ; 
 int /*<<< orphan*/  ieee80211_ageq_age (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_erp_timeout (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_ht_timeout (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_scan_timeout (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_timeout_stations (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_vht_timeout (struct ieee80211com*) ; 

void
ieee80211_node_timeout(void *arg)
{
	struct ieee80211com *ic = arg;

	/*
	 * Defer timeout processing if a channel switch is pending.
	 * We typically need to be mute so not doing things that
	 * might generate frames is good to handle in one place.
	 * Suppressing the station timeout processing may extend the
	 * lifetime of inactive stations (by not decrementing their
	 * idle counters) but this should be ok unless the CSA is
	 * active for an unusually long time.
	 */
	if ((ic->ic_flags & IEEE80211_F_CSAPENDING) == 0) {
		ieee80211_scan_timeout(ic);
		ieee80211_timeout_stations(ic);
		ieee80211_ageq_age(&ic->ic_stageq, IEEE80211_INACT_WAIT);

		IEEE80211_LOCK(ic);
		ieee80211_erp_timeout(ic);
		ieee80211_ht_timeout(ic);
		ieee80211_vht_timeout(ic);
		IEEE80211_UNLOCK(ic);
	}
	callout_reset(&ic->ic_inact, IEEE80211_INACT_WAIT*hz,
		ieee80211_node_timeout, ic);
}