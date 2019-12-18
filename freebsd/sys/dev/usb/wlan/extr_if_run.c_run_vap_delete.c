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
typedef  int uint8_t ;
struct run_vap {int rvp_id; int /*<<< orphan*/ * beacon_mbuf; } ;
struct run_softc {int ratectl_run; int rvp_bmap; int /*<<< orphan*/  rvp_cnt; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct run_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_80211_VAP ; 
 int /*<<< orphan*/  RT2860_BCN_BASE (int) ; 
 int /*<<< orphan*/  RT2860_SKEY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_DEBUG_STATE ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,struct ieee80211vap*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 struct run_vap* RUN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  free (struct run_vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ratectl_deinit (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_vap_detach (struct ieee80211vap*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_set_region_4 (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_vap_delete(struct ieee80211vap *vap)
{
	struct run_vap *rvp = RUN_VAP(vap);
	struct ieee80211com *ic;
	struct run_softc *sc;
	uint8_t rvp_id;

	if (vap == NULL)
		return;

	ic = vap->iv_ic;
	sc = ic->ic_softc;

	RUN_LOCK(sc);

	m_freem(rvp->beacon_mbuf);
	rvp->beacon_mbuf = NULL;

	rvp_id = rvp->rvp_id;
	sc->ratectl_run &= ~(1 << rvp_id);
	sc->rvp_bmap &= ~(1 << rvp_id);
	run_set_region_4(sc, RT2860_SKEY(rvp_id, 0), 0, 128);
	run_set_region_4(sc, RT2860_BCN_BASE(rvp_id), 0, 512);
	--sc->rvp_cnt;

	RUN_DPRINTF(sc, RUN_DEBUG_STATE,
	    "vap=%p rvp_id=%d bmap=%x rvp_cnt=%d\n",
	    vap, rvp_id, sc->rvp_bmap, sc->rvp_cnt);

	RUN_UNLOCK(sc);

	ieee80211_ratectl_deinit(vap);
	ieee80211_vap_detach(vap);
	free(rvp, M_80211_VAP);
}