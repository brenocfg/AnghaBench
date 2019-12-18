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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_softc {int /*<<< orphan*/  sc_txproc_cnt; int /*<<< orphan*/  sc_txrix; scalar_t__ sc_softled; scalar_t__ sc_wd_timer; TYPE_1__* sc_cabq; int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  sc_lastrx; TYPE_1__* sc_txq; int /*<<< orphan*/  sc_txq_active; } ;
struct TYPE_2__ {int /*<<< orphan*/  axq_qnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_KTR (struct ath_softc*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_KTR_TXCOMP ; 
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_PCU_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_PCU_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 scalar_t__ TXQACTIVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_gettsf64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_led_event (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_power_restore_power_state (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_power_set_power_state (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_tx_kick (struct ath_softc*) ; 
 scalar_t__ ath_tx_processq (struct ath_softc*,TYPE_1__*,int) ; 

__attribute__((used)) static void
ath_tx_proc_q0(void *arg, int npending)
{
	struct ath_softc *sc = arg;
	uint32_t txqs;

	ATH_PCU_LOCK(sc);
	sc->sc_txproc_cnt++;
	txqs = sc->sc_txq_active;
	sc->sc_txq_active &= ~txqs;
	ATH_PCU_UNLOCK(sc);

	ATH_LOCK(sc);
	ath_power_set_power_state(sc, HAL_PM_AWAKE);
	ATH_UNLOCK(sc);

	ATH_KTR(sc, ATH_KTR_TXCOMP, 1,
	    "ath_tx_proc_q0: txqs=0x%08x", txqs);

	if (TXQACTIVE(txqs, 0) && ath_tx_processq(sc, &sc->sc_txq[0], 1))
		/* XXX why is lastrx updated in tx code? */
		sc->sc_lastrx = ath_hal_gettsf64(sc->sc_ah);
	if (TXQACTIVE(txqs, sc->sc_cabq->axq_qnum))
		ath_tx_processq(sc, sc->sc_cabq, 1);
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