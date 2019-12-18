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
 int /*<<< orphan*/  CAC_TIMEOUT ; 
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_NOTIFY_CAC_START ; 
 int /*<<< orphan*/  cac_timeout ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_notify_cac (struct ieee80211com*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ticks_to_secs (int /*<<< orphan*/ ) ; 

void
ieee80211_dfs_cac_start(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_dfs_state *dfs = &ic->ic_dfs;

	IEEE80211_LOCK_ASSERT(ic);

	callout_reset(&dfs->cac_timer, CAC_TIMEOUT, cac_timeout, vap);
	if_printf(vap->iv_ifp, "start %d second CAC timer on channel %u (%u MHz)\n",
	    ticks_to_secs(CAC_TIMEOUT),
	    ic->ic_curchan->ic_ieee, ic->ic_curchan->ic_freq);
	ieee80211_notify_cac(ic, ic->ic_curchan, IEEE80211_NOTIFY_CAC_START);
}