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
struct ieee80211vap {scalar_t__ iv_state; int /*<<< orphan*/  (* iv_bmiss ) (struct ieee80211vap*) ;struct ieee80211com* iv_ic; } ;
struct ieee80211com {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*) ; 

__attribute__((used)) static void
beacon_swmiss(void *arg, int npending)
{
	struct ieee80211vap *vap = arg;
	struct ieee80211com *ic = vap->iv_ic;

	IEEE80211_LOCK(ic);
	if (vap->iv_state >= IEEE80211_S_RUN) {
		/* XXX Call multiple times if npending > zero? */
		vap->iv_bmiss(vap);
	}
	IEEE80211_UNLOCK(ic);
}