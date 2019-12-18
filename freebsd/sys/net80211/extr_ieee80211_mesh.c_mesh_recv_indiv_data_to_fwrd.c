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
struct mbuf {int dummy; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_ic; struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_qosframe_addr4 {int /*<<< orphan*/  i_addr4; int /*<<< orphan*/  i_addr3; int /*<<< orphan*/  i_addr2; } ;
struct ieee80211_meshcntl {int dummy; } ;
struct ieee80211_mesh_state {TYPE_1__* ms_ppath; } ;
struct ieee80211_mesh_route {int dummy; } ;
struct ieee80211_frame {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mpp_inact; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MSG_MESH ; 
 int /*<<< orphan*/  IEEE80211_NOTE_MAC (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IEEE80211_TX_UNLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct ieee80211_mesh_route* ieee80211_mesh_rt_find (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mesh_rt_update (struct ieee80211_mesh_route*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_forward (struct ieee80211vap*,struct mbuf*,struct ieee80211_meshcntl const*) ; 
 int /*<<< orphan*/  ticks_to_msecs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mesh_recv_indiv_data_to_fwrd(struct ieee80211vap *vap, struct mbuf *m,
    struct ieee80211_frame *wh, const struct ieee80211_meshcntl *mc)
{
	struct ieee80211_qosframe_addr4 *qwh;
	struct ieee80211_mesh_state *ms = vap->iv_mesh;
	struct ieee80211_mesh_route *rt_meshda, *rt_meshsa;

	/* This is called from the RX path - don't hold this lock */
	IEEE80211_TX_UNLOCK_ASSERT(vap->iv_ic);

	qwh = (struct ieee80211_qosframe_addr4 *)wh;

	/*
	 * TODO:
	 * o verify addr2 is  a legitimate transmitter
	 * o lifetime of precursor of addr3 (addr2) is max(init, curr)
	 * o lifetime of precursor of addr4 (nexthop) is max(init, curr)
	 */

	/* set lifetime of addr3 (meshDA) to initial value */
	rt_meshda = ieee80211_mesh_rt_find(vap, qwh->i_addr3);
	if (rt_meshda == NULL) {
		IEEE80211_NOTE_MAC(vap, IEEE80211_MSG_MESH, qwh->i_addr2,
		    "no route to meshDA(%6D)", qwh->i_addr3, ":");
		/*
		 * [Optional] any of the following three actions:
		 * o silently discard 				[X]
		 * o trigger a path discovery			[ ]
		 * o inform TA that meshDA is unknown.		[ ]
		 */
		/* XXX: stats */
		return (-1);
	}

	ieee80211_mesh_rt_update(rt_meshda, ticks_to_msecs(
	    ms->ms_ppath->mpp_inact));

	/* set lifetime of addr4 (meshSA) to initial value */
	rt_meshsa = ieee80211_mesh_rt_find(vap, qwh->i_addr4);
	KASSERT(rt_meshsa != NULL, ("no route"));
	ieee80211_mesh_rt_update(rt_meshsa, ticks_to_msecs(
	    ms->ms_ppath->mpp_inact));

	mesh_forward(vap, m, mc);
	return (1); /* dont process locally */
}