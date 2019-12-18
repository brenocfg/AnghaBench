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
struct rum_vap {int /*<<< orphan*/  bcn_mbuf; int /*<<< orphan*/  ratectl_task; int /*<<< orphan*/  ratectl_ch; } ;
struct rum_softc {int dummy; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_nstate_task; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct rum_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_S_INIT ; 
 int /*<<< orphan*/  M_80211_VAP ; 
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 struct rum_vap* RUM_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  free (struct rum_vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_new_state (struct ieee80211vap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_ratectl_deinit (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_vap_detach (struct ieee80211vap*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_reset_tx_list (struct rum_softc*,struct ieee80211vap*) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rum_vap_delete(struct ieee80211vap *vap)
{
	struct rum_vap *rvp = RUM_VAP(vap);
	struct ieee80211com *ic = vap->iv_ic;
	struct rum_softc *sc = ic->ic_softc;

	/* Put vap into INIT state. */
	ieee80211_new_state(vap, IEEE80211_S_INIT, -1);
	ieee80211_draintask(ic, &vap->iv_nstate_task);

	RUM_LOCK(sc);
	/* Cancel any unfinished Tx. */
	rum_reset_tx_list(sc, vap);
	RUM_UNLOCK(sc);

	usb_callout_drain(&rvp->ratectl_ch);
	ieee80211_draintask(ic, &rvp->ratectl_task);
	ieee80211_ratectl_deinit(vap);
	ieee80211_vap_detach(vap);
	m_freem(rvp->bcn_mbuf);
	free(rvp, M_80211_VAP);
}