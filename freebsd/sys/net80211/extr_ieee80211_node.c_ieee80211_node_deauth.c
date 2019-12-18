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
struct ieee80211_node {scalar_t__ ni_associd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_DEAUTH ; 
 int /*<<< orphan*/  IEEE80211_SEND_MGMT (struct ieee80211_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_node_leave (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_ref_node (struct ieee80211_node*) ; 

void
ieee80211_node_deauth(struct ieee80211_node *ni, int reason)
{
	/* NB: bump the refcnt to be sure temporary nodes are not reclaimed */
	ieee80211_ref_node(ni);
	if (ni->ni_associd != 0)
		IEEE80211_SEND_MGMT(ni, IEEE80211_FC0_SUBTYPE_DEAUTH, reason);
	ieee80211_node_leave(ni);
	ieee80211_free_node(ni);
}