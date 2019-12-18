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
typedef  size_t uint32_t ;
struct run_vap {int /*<<< orphan*/ * beacon_mbuf; } ;
struct run_softc {int /*<<< orphan*/  cmdq_task; TYPE_1__* cmdq; int /*<<< orphan*/  cmdq_store; } ;
struct ieee80211_beacon_offsets {int /*<<< orphan*/  bo_flags; } ;
struct ieee80211vap {struct ieee80211_node* iv_bss; struct ieee80211_beacon_offsets iv_bcn_off; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct run_softc* ic_softc; } ;
struct ieee80211_node {int dummy; } ;
struct TYPE_2__ {struct ieee80211vap* arg0; int /*<<< orphan*/  func; } ;

/* Variables and functions */
#define  IEEE80211_BEACON_ERP 130 
#define  IEEE80211_BEACON_HTINFO 129 
#define  IEEE80211_BEACON_TIM 128 
 size_t RUN_CMDQ_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RUN_DEBUG_BEACON ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,size_t) ; 
 struct run_vap* RUN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/ * ieee80211_beacon_alloc (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_beacon_update (struct ieee80211_node*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_update_beacon_cb ; 
 int /*<<< orphan*/  run_updateprot (struct ieee80211com*) ; 
 int /*<<< orphan*/  run_updateslot (struct ieee80211com*) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_update_beacon(struct ieee80211vap *vap, int item)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_beacon_offsets *bo = &vap->iv_bcn_off;
	struct ieee80211_node *ni = vap->iv_bss;
	struct run_softc *sc = ic->ic_softc;
	struct run_vap *rvp = RUN_VAP(vap);
	int mcast = 0;
	uint32_t i;

	switch (item) {
	case IEEE80211_BEACON_ERP:
		run_updateslot(ic);
		break;
	case IEEE80211_BEACON_HTINFO:
		run_updateprot(ic);
		break;
	case IEEE80211_BEACON_TIM:
		mcast = 1;	/*TODO*/
		break;
	default:
		break;
	}

	setbit(bo->bo_flags, item);
	if (rvp->beacon_mbuf == NULL) {
		rvp->beacon_mbuf = ieee80211_beacon_alloc(ni);
		if (rvp->beacon_mbuf == NULL)
			return;
	}
	ieee80211_beacon_update(ni, rvp->beacon_mbuf, mcast);

	i = RUN_CMDQ_GET(&sc->cmdq_store);
	RUN_DPRINTF(sc, RUN_DEBUG_BEACON, "cmdq_store=%d\n", i);
	sc->cmdq[i].func = run_update_beacon_cb;
	sc->cmdq[i].arg0 = vap;
	ieee80211_runtask(ic, &sc->cmdq_task);

	return;
}