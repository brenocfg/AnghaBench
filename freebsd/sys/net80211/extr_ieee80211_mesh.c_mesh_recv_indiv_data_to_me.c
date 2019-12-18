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
struct ieee80211_qosframe_addr4 {int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr3; int /*<<< orphan*/  i_addr4; } ;
struct ieee80211_meshcntl_ae10 {int mc_flags; int /*<<< orphan*/  mc_addr5; int /*<<< orphan*/  mc_addr6; } ;
struct ieee80211_meshcntl {int dummy; } ;
struct ieee80211_mesh_state {TYPE_1__* ms_ppath; } ;
struct ieee80211_mesh_route {int rt_flags; } ;
struct ieee80211_frame {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mpp_inact; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_MESHRT_FLAGS_PROXY ; 
 int IEEE80211_MESHRT_FLAGS_VALID ; 
 int IEEE80211_MESH_AE_00 ; 
 int IEEE80211_MESH_AE_10 ; 
 int IEEE80211_MESH_AE_MASK ; 
 int /*<<< orphan*/  IEEE80211_MSG_OUTPUT ; 
 int /*<<< orphan*/  IEEE80211_NOTE_MAC (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IEEE80211_TX_UNLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct ieee80211_mesh_route* ieee80211_mesh_rt_find (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mesh_rt_update (struct ieee80211_mesh_route*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_forward (struct ieee80211vap*,struct mbuf*,struct ieee80211_meshcntl const*) ; 
 int /*<<< orphan*/  ticks_to_msecs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mesh_recv_indiv_data_to_me(struct ieee80211vap *vap, struct mbuf *m,
    struct ieee80211_frame *wh, const struct ieee80211_meshcntl *mc)
{
	struct ieee80211_qosframe_addr4 *qwh;
	const struct ieee80211_meshcntl_ae10 *mc10;
	struct ieee80211_mesh_state *ms = vap->iv_mesh;
	struct ieee80211_mesh_route *rt;
	int ae;

	/* This is called from the RX path - don't hold this lock */
	IEEE80211_TX_UNLOCK_ASSERT(vap->iv_ic);

	qwh = (struct ieee80211_qosframe_addr4 *)wh;
	mc10 = (const struct ieee80211_meshcntl_ae10 *)mc;

	/*
	 * TODO:
	 * o verify addr2 is  a legitimate transmitter
	 * o lifetime of precursor entry is max(init, curr)
	 */

	/* set lifetime of addr4 (meshSA) to initial value */
	rt = ieee80211_mesh_rt_find(vap, qwh->i_addr4);
	KASSERT(rt != NULL, ("no route"));
	ieee80211_mesh_rt_update(rt, ticks_to_msecs(ms->ms_ppath->mpp_inact));
	rt = NULL;

	ae = mc10->mc_flags & IEEE80211_MESH_AE_MASK;
	KASSERT(ae == IEEE80211_MESH_AE_00 ||
	    ae == IEEE80211_MESH_AE_10, ("bad AE %d", ae));
	if (ae == IEEE80211_MESH_AE_10) {
		if (IEEE80211_ADDR_EQ(mc10->mc_addr5, qwh->i_addr3)) {
			return (0); /* process locally */
		}

		rt =  ieee80211_mesh_rt_find(vap, mc10->mc_addr5);
		if (rt != NULL &&
		    (rt->rt_flags & IEEE80211_MESHRT_FLAGS_VALID) &&
		    (rt->rt_flags & IEEE80211_MESHRT_FLAGS_PROXY) == 0) {
			/*
			 * Forward on another mesh-path, according to
			 * amendment as specified in 9.32.4.1
			 */
			IEEE80211_ADDR_COPY(qwh->i_addr3, mc10->mc_addr5);
			mesh_forward(vap, m,
			    (const struct ieee80211_meshcntl *)mc10);
			return (1); /* dont process locally */
		}
		/*
		 * All other cases: forward of MSDUs from the MBSS to DS indiv.
		 * addressed according to 13.11.3.2.
		 */
		IEEE80211_NOTE_MAC(vap, IEEE80211_MSG_OUTPUT, qwh->i_addr2,
		    "forward frame to DS, SA(%6D) DA(%6D)",
		    mc10->mc_addr6, ":", mc10->mc_addr5, ":");
	}
	return (0); /* process locally */
}