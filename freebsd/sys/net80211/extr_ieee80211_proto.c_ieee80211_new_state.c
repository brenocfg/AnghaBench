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
struct ieee80211com {int dummy; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int ieee80211_new_state_locked (struct ieee80211vap*,int,int) ; 

int
ieee80211_new_state(struct ieee80211vap *vap,
	enum ieee80211_state nstate, int arg)
{
	struct ieee80211com *ic = vap->iv_ic;
	int rc;

	IEEE80211_LOCK(ic);
	rc = ieee80211_new_state_locked(vap, nstate, arg);
	IEEE80211_UNLOCK(ic);
	return rc;
}