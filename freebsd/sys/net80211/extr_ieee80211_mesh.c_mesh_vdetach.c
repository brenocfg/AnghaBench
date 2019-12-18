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
struct ieee80211vap {struct ieee80211_mesh_state* iv_mesh; TYPE_1__* iv_ic; } ;
struct ieee80211_mesh_state {TYPE_2__* ms_ppath; int /*<<< orphan*/  ms_cleantimer; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* mpp_vdetach ) (struct ieee80211vap*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  ic_sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (struct ieee80211_mesh_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MESH_RT_LOCK_DESTROY (struct ieee80211_mesh_state*) ; 
 int /*<<< orphan*/  M_80211_VAP ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_iterate_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_mesh_rt_flush (struct ieee80211vap*) ; 
 int /*<<< orphan*/  mesh_vdetach_peers ; 
 int /*<<< orphan*/  stub1 (struct ieee80211vap*) ; 

__attribute__((used)) static void
mesh_vdetach(struct ieee80211vap *vap)
{
	struct ieee80211_mesh_state *ms = vap->iv_mesh;

	callout_drain(&ms->ms_cleantimer);
	ieee80211_iterate_nodes(&vap->iv_ic->ic_sta, mesh_vdetach_peers,
	    NULL);
	ieee80211_mesh_rt_flush(vap);
	MESH_RT_LOCK_DESTROY(ms);
	ms->ms_ppath->mpp_vdetach(vap);
	IEEE80211_FREE(vap->iv_mesh, M_80211_VAP);
	vap->iv_mesh = NULL;
}