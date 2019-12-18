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
struct ieee80211_node {int ni_mlstate; scalar_t__ ni_mltval; int /*<<< orphan*/  ni_mltimer; } ;

/* Variables and functions */
#define  IEEE80211_NODE_MESH_CONFIRMRCV 130 
#define  IEEE80211_NODE_MESH_HOLDING 129 
#define  IEEE80211_NODE_MESH_IDLE 128 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct ieee80211_node*) ; 
 scalar_t__ ieee80211_mesh_confirmtimeout ; 
 scalar_t__ ieee80211_mesh_holdingtimeout ; 
 scalar_t__ ieee80211_mesh_retrytimeout ; 
 int /*<<< orphan*/  mesh_peer_timeout_cb ; 

__attribute__((used)) static void
mesh_peer_timeout_setup(struct ieee80211_node *ni)
{
	switch (ni->ni_mlstate) {
	case IEEE80211_NODE_MESH_HOLDING:
		ni->ni_mltval = ieee80211_mesh_holdingtimeout;
		break;
	case IEEE80211_NODE_MESH_CONFIRMRCV:
		ni->ni_mltval = ieee80211_mesh_confirmtimeout;
		break;
	case IEEE80211_NODE_MESH_IDLE:
		ni->ni_mltval = 0;
		break;
	default:
		ni->ni_mltval = ieee80211_mesh_retrytimeout;
		break;
	}
	if (ni->ni_mltval)
		callout_reset(&ni->ni_mltimer, ni->ni_mltval,
		    mesh_peer_timeout_cb, ni);
}