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
struct ifnet {int /*<<< orphan*/  if_vnet; } ;
struct ieee80211vap {struct ifnet* iv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_DPRINTF (struct ieee80211vap*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  IEEE80211_MSG_SCAN ; 
 int /*<<< orphan*/  RTM_IEEE80211_SCAN ; 
 int /*<<< orphan*/  rt_ieee80211msg (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ieee80211_notify_scan_done(struct ieee80211vap *vap)
{
	struct ifnet *ifp = vap->iv_ifp;

	IEEE80211_DPRINTF(vap, IEEE80211_MSG_SCAN, "%s\n", "notify scan done");

	/* dispatch wireless event indicating scan completed */
	CURVNET_SET(ifp->if_vnet);
	rt_ieee80211msg(ifp, RTM_IEEE80211_SCAN, NULL, 0);
	CURVNET_RESTORE();
}