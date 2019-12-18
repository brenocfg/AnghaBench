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
struct ifnet {struct ieee80211vap* if_softc; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  (* ic_vap_delete ) (struct ieee80211vap*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ieee80211vap*) ; 

__attribute__((used)) static void
wlan_clone_destroy(struct ifnet *ifp)
{
	struct ieee80211vap *vap = ifp->if_softc;
	struct ieee80211com *ic = vap->iv_ic;

	ic->ic_vap_delete(vap);
}