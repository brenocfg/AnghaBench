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
struct ieee80211com {int /*<<< orphan*/  ic_sta; int /*<<< orphan*/  ic_vaps; } ;
struct run_softc {int rvp_cnt; scalar_t__ ratectl_run; int /*<<< orphan*/  ratectl_ch; struct ieee80211com sc_ic; } ;
struct ieee80211vap {scalar_t__ iv_opmode; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_STA ; 
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 scalar_t__ RUN_RATECTL_OFF ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ieee80211_iterate_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct run_softc*) ; 
 int /*<<< orphan*/  run_drain_fifo (struct run_softc*) ; 
 int /*<<< orphan*/  run_iter_func ; 
 int /*<<< orphan*/  run_ratectl_to ; 
 int /*<<< orphan*/  run_reset_livelock (struct run_softc*) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct run_softc*) ; 

__attribute__((used)) static void
run_ratectl_cb(void *arg, int pending)
{
	struct run_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);

	if (vap == NULL)
		return;

	if (sc->rvp_cnt > 1 || vap->iv_opmode != IEEE80211_M_STA) {
		/*
		 * run_reset_livelock() doesn't do anything with AMRR,
		 * but Ralink wants us to call it every 1 sec. So, we
		 * piggyback here rather than creating another callout.
		 * Livelock may occur only in HOSTAP or IBSS mode
		 * (when h/w is sending beacons).
		 */
		RUN_LOCK(sc);
		run_reset_livelock(sc);
		/* just in case, there are some stats to drain */
		run_drain_fifo(sc);
		RUN_UNLOCK(sc);
	}

	ieee80211_iterate_nodes(&ic->ic_sta, run_iter_func, sc);

	RUN_LOCK(sc);
	if(sc->ratectl_run != RUN_RATECTL_OFF)
		usb_callout_reset(&sc->ratectl_ch, hz, run_ratectl_to, sc);
	RUN_UNLOCK(sc);
}