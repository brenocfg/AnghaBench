#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_mlhtimer; int /*<<< orphan*/  ni_mltimer; struct ieee80211vap* ni_vap; } ;
struct ieee80211_mesh_state {TYPE_1__* ms_ppath; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mpp_peerdown ) (struct ieee80211_node*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*) ; 

void
ieee80211_mesh_node_cleanup(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211_mesh_state *ms = vap->iv_mesh;

	callout_drain(&ni->ni_mltimer);
	callout_drain(&ni->ni_mlhtimer);
	/* NB: short-circuit callbacks after mesh_vdetach */
	if (vap->iv_mesh != NULL)
		ms->ms_ppath->mpp_peerdown(ni);
}