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
struct rtwn_vap {int /*<<< orphan*/  tsf_sync_adhoc; int /*<<< orphan*/  tsf_sync_adhoc_task; int /*<<< orphan*/  id; int /*<<< orphan*/ * bcn_mbuf; } ;
struct rtwn_softc {int sc_flags; } ;
struct ieee80211vap {scalar_t__ iv_opmode; int /*<<< orphan*/  iv_nstate_task; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_parent_task; struct rtwn_softc* ic_softc; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_IBSS ; 
 int /*<<< orphan*/  M_80211_VAP ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int RTWN_RUNNING ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 struct rtwn_vap* RTWN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct rtwn_vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ratectl_deinit (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_stop (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_vap_detach (struct ieee80211vap*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtwn_reset_lists (struct rtwn_softc*,struct ieee80211vap*) ; 
 int /*<<< orphan*/  rtwn_rxfilter_update (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_set_ic_opmode (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_vap_decrement_counters (struct rtwn_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtwn_vap_delete(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct rtwn_softc *sc = ic->ic_softc;
	struct rtwn_vap *uvp = RTWN_VAP(vap);

	/* Put vap into INIT state + stop device if needed. */
	ieee80211_stop(vap);
	ieee80211_draintask(ic, &vap->iv_nstate_task);
	ieee80211_draintask(ic, &ic->ic_parent_task);

	RTWN_LOCK(sc);
	/* Cancel any unfinished Tx. */
	rtwn_reset_lists(sc, vap);
	if (uvp->bcn_mbuf != NULL)
		m_freem(uvp->bcn_mbuf);
	rtwn_vap_decrement_counters(sc, vap->iv_opmode, uvp->id);
	rtwn_set_ic_opmode(sc);
	if (sc->sc_flags & RTWN_RUNNING)
		rtwn_rxfilter_update(sc);
	RTWN_UNLOCK(sc);

	if (vap->iv_opmode == IEEE80211_M_IBSS) {
		ieee80211_draintask(ic, &uvp->tsf_sync_adhoc_task);
		callout_drain(&uvp->tsf_sync_adhoc);
	}

	ieee80211_ratectl_deinit(vap);
	ieee80211_vap_detach(vap);
	free(uvp, M_80211_VAP);
}