#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {TYPE_2__* ic_scan_methods; struct ieee80211_scan_state* ic_scan; } ;
struct ieee80211_scan_state {struct ieee80211vap* ss_vap; TYPE_1__* ss_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sc_vdetach ) (struct ieee80211vap*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* scan_detach ) (struct ieee80211_scan_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_scan_state*) ; 

void
ieee80211_scan_vdetach(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_scan_state *ss;

	IEEE80211_LOCK(ic);
	ss = ic->ic_scan;

	ic->ic_scan_methods->sc_vdetach(vap);

	if (ss != NULL && ss->ss_vap == vap) {
		if (ss->ss_ops != NULL) {
			ss->ss_ops->scan_detach(ss);
			ss->ss_ops = NULL;
		}
		ss->ss_vap = NULL;
	}
	IEEE80211_UNLOCK(ic);
}