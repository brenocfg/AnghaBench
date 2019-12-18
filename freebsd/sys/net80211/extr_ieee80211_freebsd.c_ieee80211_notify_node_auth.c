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
 int /*<<< orphan*/  IEEE80211_MSG_NODE ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int /*<<< orphan*/ ,struct ieee80211_node*,char*,char*) ; 
 int /*<<< orphan*/  RTM_IEEE80211_AUTH ; 
 int /*<<< orphan*/  notify_macaddr (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ieee80211_notify_node_auth(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct ifnet *ifp = vap->iv_ifp;

	IEEE80211_NOTE(vap, IEEE80211_MSG_NODE, ni, "%s", "node auth");

	notify_macaddr(ifp, RTM_IEEE80211_AUTH, ni->ni_macaddr);
}