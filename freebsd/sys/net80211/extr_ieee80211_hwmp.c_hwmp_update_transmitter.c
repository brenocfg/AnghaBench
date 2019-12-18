#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  is_mesh_rtaddfailed; } ;
struct ieee80211vap {TYPE_1__ iv_stats; struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; } ;
struct ieee80211_mesh_state {TYPE_3__* ms_ppath; TYPE_2__* ms_pmetric; } ;
struct ieee80211_mesh_route {int rt_flags; int rt_metric; int rt_nhops; int /*<<< orphan*/  rt_nexthop; } ;
struct TYPE_6__ {int /*<<< orphan*/  mpp_inact; } ;
struct TYPE_5__ {int (* mpm_metric ) (struct ieee80211_node*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_MESHRT_FLAGS_VALID ; 
 int /*<<< orphan*/  IEEE80211_MSG_HWMP ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int /*<<< orphan*/ ,struct ieee80211_node*,char*,char*,char*,char const*,...) ; 
 struct ieee80211_mesh_route* ieee80211_mesh_rt_add (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 struct ieee80211_mesh_route* ieee80211_mesh_rt_find (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mesh_rt_update (struct ieee80211_mesh_route*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ieee80211_node*) ; 

__attribute__((used)) static void
hwmp_update_transmitter(struct ieee80211vap *vap, struct ieee80211_node *ni,
    const char *hwmp_frame)
{
	struct ieee80211_mesh_state *ms = vap->iv_mesh;
	struct ieee80211_mesh_route *rttran = NULL;	/* Transmitter */
	int metric = 0;

	rttran = ieee80211_mesh_rt_find(vap, ni->ni_macaddr);
	if (rttran == NULL) {
		rttran = ieee80211_mesh_rt_add(vap, ni->ni_macaddr);
		if (rttran == NULL) {
			IEEE80211_NOTE(vap, IEEE80211_MSG_HWMP, ni,
			    "unable to add path to transmitter %6D of %s",
			    ni->ni_macaddr, ":", hwmp_frame);
			vap->iv_stats.is_mesh_rtaddfailed++;
			return;
		}
	}
	metric = ms->ms_pmetric->mpm_metric(ni);
	if (!(rttran->rt_flags & IEEE80211_MESHRT_FLAGS_VALID) ||
	    rttran->rt_metric > metric)
	{
		IEEE80211_NOTE(vap, IEEE80211_MSG_HWMP, ni,
		    "%s path to transmitter %6D of %s, metric %d:%d",
		    rttran->rt_flags & IEEE80211_MESHRT_FLAGS_VALID ?
		    "prefer" : "update", ni->ni_macaddr, ":", hwmp_frame,
		    rttran->rt_metric, metric);
		IEEE80211_ADDR_COPY(rttran->rt_nexthop, ni->ni_macaddr);
		rttran->rt_metric = metric;
		rttran->rt_nhops  = 1;
		ieee80211_mesh_rt_update(rttran, ms->ms_ppath->mpp_inact);
		rttran->rt_flags = IEEE80211_MESHRT_FLAGS_VALID;
	}
}