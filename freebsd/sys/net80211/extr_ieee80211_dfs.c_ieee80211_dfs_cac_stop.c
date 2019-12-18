#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {int /*<<< orphan*/  iv_ifp; struct ieee80211com* iv_ic; } ;
struct ieee80211_dfs_state {int /*<<< orphan*/  cac_timer; } ;
struct ieee80211com {TYPE_1__* ic_curchan; struct ieee80211_dfs_state ic_dfs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ic_freq; int /*<<< orphan*/  ic_ieee; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_NOTIFY_CAC_STOP ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_notify_cac (struct ieee80211com*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ieee80211_dfs_cac_stop(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_dfs_state *dfs = &ic->ic_dfs;

	IEEE80211_LOCK_ASSERT(ic);

	/* NB: racey but not important */
	if (callout_pending(&dfs->cac_timer)) {
		if_printf(vap->iv_ifp, "stop CAC timer on channel %u (%u MHz)\n",
		    ic->ic_curchan->ic_ieee, ic->ic_curchan->ic_freq);
		ieee80211_notify_cac(ic, ic->ic_curchan,
		    IEEE80211_NOTIFY_CAC_STOP);
	}
	callout_stop(&dfs->cac_timer);
}