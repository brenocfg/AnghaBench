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
struct ieee80211com {int ic_caps; } ;

/* Variables and functions */
 int IEEE80211_C_WME ; 
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_wme_updateparams_locked (struct ieee80211vap*) ; 

void
ieee80211_wme_updateparams(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;

	if (ic->ic_caps & IEEE80211_C_WME) {
		IEEE80211_LOCK(ic);
		ieee80211_wme_updateparams_locked(vap);
		IEEE80211_UNLOCK(ic);
	}
}