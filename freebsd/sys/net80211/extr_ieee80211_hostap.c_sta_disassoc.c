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
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_DISASSOC ; 
 int /*<<< orphan*/  IEEE80211_REASON_ASSOC_LEAVE ; 
 int /*<<< orphan*/  IEEE80211_SEND_MGMT (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_node_leave (struct ieee80211_node*) ; 

__attribute__((used)) static void
sta_disassoc(void *arg, struct ieee80211_node *ni)
{

	if (ni->ni_associd != 0) {
		IEEE80211_SEND_MGMT(ni, IEEE80211_FC0_SUBTYPE_DISASSOC,
			IEEE80211_REASON_ASSOC_LEAVE);
		ieee80211_node_leave(ni);
	}
}