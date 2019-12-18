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
struct ath_softc {int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  sc_alq; int /*<<< orphan*/  sc_rc; TYPE_1__* sc_tx99; int /*<<< orphan*/  sc_tq; int /*<<< orphan*/  sc_ic; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  ath_btcoex_detach (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_desc_free (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_dfs_detach (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_hal_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_lna_div_detach (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_power_setpower (struct ath_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_rate_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_rxdma_teardown (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_spectral_detach (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_stop (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_tx_cleanup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_txdma_teardown (struct ath_softc*) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_ath_alq_tidyup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

int
ath_detach(struct ath_softc *sc)
{

	/*
	 * NB: the order of these is important:
	 * o stop the chip so no more interrupts will fire
	 * o call the 802.11 layer before detaching the hal to
	 *   insure callbacks into the driver to delete global
	 *   key cache entries can be handled
	 * o free the taskqueue which drains any pending tasks
	 * o reclaim the tx queue data structures after calling
	 *   the 802.11 layer as we'll get called back to reclaim
	 *   node state and potentially want to use them
	 * o to cleanup the tx queues the hal is called, so detach
	 *   it last
	 * Other than that, it's straightforward...
	 */

	/*
	 * XXX Wake the hardware up first.  ath_stop() will still
	 * wake it up first, but I'd rather do it here just to
	 * ensure it's awake.
	 */
	ATH_LOCK(sc);
	ath_power_set_power_state(sc, HAL_PM_AWAKE);
	ath_power_setpower(sc, HAL_PM_AWAKE, 1);

	/*
	 * Stop things cleanly.
	 */
	ath_stop(sc);
	ATH_UNLOCK(sc);

	ieee80211_ifdetach(&sc->sc_ic);
	taskqueue_free(sc->sc_tq);
#ifdef ATH_TX99_DIAG
	if (sc->sc_tx99 != NULL)
		sc->sc_tx99->detach(sc->sc_tx99);
#endif
	ath_rate_detach(sc->sc_rc);
#ifdef	ATH_DEBUG_ALQ
	if_ath_alq_tidyup(&sc->sc_alq);
#endif
	ath_lna_div_detach(sc);
	ath_btcoex_detach(sc);
	ath_spectral_detach(sc);
	ath_dfs_detach(sc);
	ath_desc_free(sc);
	ath_txdma_teardown(sc);
	ath_rxdma_teardown(sc);
	ath_tx_cleanup(sc);
	ath_hal_detach(sc->sc_ah);	/* NB: sets chip in full sleep */

	return 0;
}