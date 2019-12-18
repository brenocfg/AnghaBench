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
struct rtwn_vap {int /*<<< orphan*/  tsf_sync_adhoc; int /*<<< orphan*/  id; } ;
struct rtwn_softc {int /*<<< orphan*/  sc_flags; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_bss; TYPE_1__* iv_ic; } ;
struct ieee80211_node {int ni_intval; } ;
struct TYPE_2__ {struct rtwn_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_BCN_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_BCN_CTRL_DIS_TSF_UDT0 ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_RCR_LOCKED ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 struct rtwn_vap* RTWN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ieee80211vap*) ; 
 int hz ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 struct ieee80211_node* ieee80211_ref_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_delay (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_set_rx_bssid_all (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_tsf_sync_adhoc ; 

__attribute__((used)) static void
rtwn_tsf_sync_adhoc_task(void *arg, int pending)
{
	struct ieee80211vap *vap = arg;
	struct rtwn_vap *uvp = RTWN_VAP(vap);
	struct rtwn_softc *sc = vap->iv_ic->ic_softc;
	struct ieee80211_node *ni;

	RTWN_LOCK(sc);
	ni = ieee80211_ref_node(vap->iv_bss);

	/* Accept beacons with the same BSSID. */
	rtwn_set_rx_bssid_all(sc, 0);

	/* Deny RCR updates. */
	sc->sc_flags |= RTWN_RCR_LOCKED;

	/* Enable synchronization. */
	rtwn_setbits_1(sc, R92C_BCN_CTRL(uvp->id),
	    R92C_BCN_CTRL_DIS_TSF_UDT0, 0);

	/* Synchronize. */
	rtwn_delay(sc, ni->ni_intval * 5 * 1000);

	/* Disable synchronization. */
	rtwn_setbits_1(sc, R92C_BCN_CTRL(uvp->id),
	    0, R92C_BCN_CTRL_DIS_TSF_UDT0);

	/* Accept all beacons. */
	sc->sc_flags &= ~RTWN_RCR_LOCKED;
	rtwn_set_rx_bssid_all(sc, 1);

	/* Schedule next TSF synchronization. */
	callout_reset(&uvp->tsf_sync_adhoc, 60*hz, rtwn_tsf_sync_adhoc, vap);

	ieee80211_free_node(ni);
	RTWN_UNLOCK(sc);
}