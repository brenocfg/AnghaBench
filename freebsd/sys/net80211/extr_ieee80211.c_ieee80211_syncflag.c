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
struct ieee80211vap {int iv_flags; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_syncflag_locked (struct ieee80211com*,int) ; 

void
ieee80211_syncflag(struct ieee80211vap *vap, int flag)
{
	struct ieee80211com *ic = vap->iv_ic;

	IEEE80211_LOCK(ic);
	if (flag < 0) {
		flag = -flag;
		vap->iv_flags &= ~flag;
	} else
		vap->iv_flags |= flag;
	ieee80211_syncflag_locked(ic, flag);
	IEEE80211_UNLOCK(ic);
}