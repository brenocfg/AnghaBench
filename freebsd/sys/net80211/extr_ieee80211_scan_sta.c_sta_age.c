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
struct ieee80211vap {scalar_t__ iv_opmode; scalar_t__ iv_roaming; int iv_flags; scalar_t__ iv_state; } ;
struct ieee80211_scan_state {struct ieee80211vap* ss_vap; } ;

/* Variables and functions */
 int IEEE80211_F_BGSCAN ; 
 scalar_t__ IEEE80211_M_STA ; 
 scalar_t__ IEEE80211_ROAMING_AUTO ; 
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  adhoc_age (struct ieee80211_scan_state*) ; 
 int /*<<< orphan*/  sta_roam_check (struct ieee80211_scan_state*,struct ieee80211vap*) ; 

__attribute__((used)) static void
sta_age(struct ieee80211_scan_state *ss)
{
	struct ieee80211vap *vap = ss->ss_vap;

	adhoc_age(ss);
	/*
	 * If rate control is enabled check periodically to see if
	 * we should roam from our current connection to one that
	 * might be better.  This only applies when we're operating
	 * in sta mode and automatic roaming is set.
	 * XXX defer if busy
	 * XXX repeater station
	 * XXX do when !bgscan?
	 */
	KASSERT(vap->iv_opmode == IEEE80211_M_STA,
		("wrong mode %u", vap->iv_opmode));
	if (vap->iv_roaming == IEEE80211_ROAMING_AUTO &&
	    (vap->iv_flags & IEEE80211_F_BGSCAN) &&
	    vap->iv_state >= IEEE80211_S_RUN)
		/* XXX vap is implicit */
		sta_roam_check(ss, vap);
}