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
struct iwm_softc {int sc_flags; int /*<<< orphan*/  sc_es_task; } ;
struct ieee80211vap {scalar_t__ iv_state; } ;
struct ieee80211com {int /*<<< orphan*/  ic_tq; struct iwm_softc* ic_softc; int /*<<< orphan*/  ic_vaps; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_S_RUN ; 
 int IWM_FLAG_SCAN_RUNNING ; 
 int /*<<< orphan*/  IWM_LOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  IWM_UNLOCK (struct iwm_softc*) ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_led_blink_stop (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_mvm_led_enable (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_mvm_scan_stop_wait (struct iwm_softc*) ; 
 int /*<<< orphan*/  taskqueue_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iwm_scan_end(struct ieee80211com *ic)
{
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	struct iwm_softc *sc = ic->ic_softc;

	IWM_LOCK(sc);
	iwm_led_blink_stop(sc);
	if (vap->iv_state == IEEE80211_S_RUN)
		iwm_mvm_led_enable(sc);
	if (sc->sc_flags & IWM_FLAG_SCAN_RUNNING) {
		/*
		 * Removing IWM_FLAG_SCAN_RUNNING now, is fine because
		 * both iwm_scan_end and iwm_scan_start run in the ic->ic_tq
		 * taskqueue.
		 */
		sc->sc_flags &= ~IWM_FLAG_SCAN_RUNNING;
		iwm_mvm_scan_stop_wait(sc);
	}
	IWM_UNLOCK(sc);

	/*
	 * Make sure we don't race, if sc_es_task is still enqueued here.
	 * This is to make sure that it won't call ieee80211_scan_done
	 * when we have already started the next scan.
	 */
	taskqueue_cancel(ic->ic_tq, &sc->sc_es_task, NULL);
}