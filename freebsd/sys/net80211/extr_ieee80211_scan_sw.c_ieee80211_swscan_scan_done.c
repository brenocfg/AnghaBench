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
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct ieee80211_scan_state* ic_scan; } ;
struct ieee80211_scan_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int /*<<< orphan*/  scan_signal_locked (struct ieee80211_scan_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ieee80211_swscan_scan_done(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_state *ss = ic->ic_scan;

	IEEE80211_LOCK_ASSERT(ic);

	scan_signal_locked(ss, 0);
}