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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_softc {int /*<<< orphan*/  sc_txproc_cnt; int /*<<< orphan*/  sc_txrix; scalar_t__ sc_softled; scalar_t__ sc_wd_timer; int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  sc_lastrx; int /*<<< orphan*/ * sc_txq; int /*<<< orphan*/  sc_txq_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_KTR (struct ath_softc*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_KTR_TXCOMP ; 
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_PCU_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_PCU_UNLOCK (struct ath_softc*) ; 
 scalar_t__ ATH_TXQ_SETUP (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int HAL_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 scalar_t__ TXQACTIVE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_hal_gettsf64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_led_event (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_power_restore_power_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_tx_kick (struct ath_softc*) ; 
 scalar_t__ ath_tx_processq (struct ath_softc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ath_tx_proc(void *arg, int npending)
{
	struct ath_softc *sc = arg;
	int i, nacked;
	uint32_t txqs;

	ATH_PCU_LOCK(sc);
	sc->sc_txproc_cnt++;
	txqs = sc->sc_txq_active;
	sc->sc_txq_active &= ~txqs;
	ATH_PCU_UNLOCK(sc);

	ATH_LOCK(sc);
	ath_power_set_power_state(sc, HAL_PM_AWAKE);
	ATH_UNLOCK(sc);

	ATH_KTR(sc, ATH_KTR_TXCOMP, 1, "ath_tx_proc: txqs=0x%08x", txqs);

	/*
	 * Process each active queue.
	 */
	nacked = 0;
	for (i = 0; i < HAL_NUM_TX_QUEUES; i++)
		if (ATH_TXQ_SETUP(sc, i) && TXQACTIVE(txqs, i))
			nacked += ath_tx_processq(sc, &sc->sc_txq[i], 1);
	if (nacked)
		sc->sc_lastrx = ath_hal_gettsf64(sc->sc_ah);

	sc->sc_wd_timer = 0;

	if (sc->sc_softled)
		ath_led_event(sc, sc->sc_txrix);

	ATH_PCU_LOCK(sc);
	sc->sc_txproc_cnt--;
	ATH_PCU_UNLOCK(sc);

	ATH_LOCK(sc);
	ath_power_restore_power_state(sc);
	ATH_UNLOCK(sc);

	ath_tx_kick(sc);
}