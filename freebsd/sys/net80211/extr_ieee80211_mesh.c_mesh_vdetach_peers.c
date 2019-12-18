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
typedef  int /*<<< orphan*/  uint16_t ;
struct ieee80211com {int /*<<< orphan*/  ic_stageq; } ;
struct ieee80211_node {scalar_t__ ni_mlstate; int /*<<< orphan*/  ni_macaddr; int /*<<< orphan*/  ni_mltimer; int /*<<< orphan*/  ni_mllid; int /*<<< orphan*/  ni_mlpid; struct ieee80211com* ni_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ACTION_CAT_SELF_PROT ; 
 int /*<<< orphan*/  IEEE80211_ACTION_MESHPEERING_CLOSE ; 
 scalar_t__ IEEE80211_NODE_MESH_ESTABLISHED ; 
 int /*<<< orphan*/  IEEE80211_REASON_PEER_LINK_CANCELED ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ageq_drain_node (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ ieee80211_mac_hash (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_action (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mesh_vdetach_peers(void *arg, struct ieee80211_node *ni)
{
	struct ieee80211com *ic = ni->ni_ic;
	uint16_t args[3];

	if (ni->ni_mlstate == IEEE80211_NODE_MESH_ESTABLISHED) {
		args[0] = ni->ni_mlpid;
		args[1] = ni->ni_mllid;
		args[2] = IEEE80211_REASON_PEER_LINK_CANCELED;
		ieee80211_send_action(ni,
		    IEEE80211_ACTION_CAT_SELF_PROT,
		    IEEE80211_ACTION_MESHPEERING_CLOSE,
		    args);
	}
	callout_drain(&ni->ni_mltimer);
	/* XXX belongs in hwmp */
	ieee80211_ageq_drain_node(&ic->ic_stageq,
	   (void *)(uintptr_t) ieee80211_mac_hash(ic, ni->ni_macaddr));
}