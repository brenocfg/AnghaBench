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
typedef  int /*<<< orphan*/  u_int ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct ieee80211_scan_state* ic_scan; } ;
struct ieee80211_scan_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ss_duration; int /*<<< orphan*/  ss_iflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int /*<<< orphan*/  ISCAN_DISCARD ; 
 TYPE_1__* SCAN_PRIVATE (struct ieee80211_scan_state*) ; 

__attribute__((used)) static void
ieee80211_swscan_set_scan_duration(struct ieee80211vap *vap, u_int duration)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_state *ss = ic->ic_scan;

	IEEE80211_LOCK_ASSERT(ic);

	/* NB: flush frames rx'd before 1st channel change */
	SCAN_PRIVATE(ss)->ss_iflags |= ISCAN_DISCARD;
	SCAN_PRIVATE(ss)->ss_duration = duration;
}