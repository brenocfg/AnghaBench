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
struct ifnet {int dummy; } ;
struct ieee80211vap {struct ifnet* iv_ifp; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_IEEE80211_WDS ; 
 int /*<<< orphan*/  notify_macaddr (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ieee80211_notify_wds_discover(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct ifnet *ifp = vap->iv_ifp;

	notify_macaddr(ifp, RTM_IEEE80211_WDS, ni->ni_macaddr);
}