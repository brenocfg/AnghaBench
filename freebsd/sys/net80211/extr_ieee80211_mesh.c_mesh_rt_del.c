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
struct ieee80211_mesh_state {int /*<<< orphan*/  ms_routes; } ;
struct ieee80211_mesh_route {int /*<<< orphan*/  rt_discovery; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (struct ieee80211_mesh_route*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MESH_RT_ENTRY_LOCK (struct ieee80211_mesh_route*) ; 
 int /*<<< orphan*/  MESH_RT_ENTRY_LOCK_DESTROY (struct ieee80211_mesh_route*) ; 
 int /*<<< orphan*/  M_80211_MESH_RT ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ieee80211_mesh_route*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_next ; 

__attribute__((used)) static __inline void
mesh_rt_del(struct ieee80211_mesh_state *ms, struct ieee80211_mesh_route *rt)
{
	TAILQ_REMOVE(&ms->ms_routes, rt, rt_next);
	/*
	 * Grab the lock before destroying it, to be sure no one else
	 * is holding the route.
	 */
	MESH_RT_ENTRY_LOCK(rt);
	callout_drain(&rt->rt_discovery);
	MESH_RT_ENTRY_LOCK_DESTROY(rt);
	IEEE80211_FREE(rt, M_80211_MESH_RT);
}