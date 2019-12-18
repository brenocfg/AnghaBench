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
struct iwi_softc {int flags; int /*<<< orphan*/  fw_state; scalar_t__ sc_busy_timer; scalar_t__ sc_state_timer; scalar_t__ sc_tx_timer; int /*<<< orphan*/  rxq; int /*<<< orphan*/ * txq; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  sc_rftimer; int /*<<< orphan*/  sc_wdtimer; scalar_t__ sc_blinking; int /*<<< orphan*/  sc_ledtimer; scalar_t__ sc_softled; scalar_t__ sc_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct iwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWI_CSR_RST ; 
 int IWI_FLAG_ASSOCIATED ; 
 int IWI_FLAG_BUSY ; 
 int /*<<< orphan*/  IWI_FW_IDLE ; 
 int /*<<< orphan*/  IWI_LOCK_ASSERT (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_RST_SOFT_RESET ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwi_reset_cmd_ring (struct iwi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwi_reset_rx_ring (struct iwi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwi_reset_tx_ring (struct iwi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwi_stop_master (struct iwi_softc*) ; 
 int /*<<< orphan*/  wakeup (struct iwi_softc*) ; 

__attribute__((used)) static void
iwi_stop_locked(void *priv)
{
	struct iwi_softc *sc = priv;

	IWI_LOCK_ASSERT(sc);

	sc->sc_running = 0;

	if (sc->sc_softled) {
		callout_stop(&sc->sc_ledtimer);
		sc->sc_blinking = 0;
	}
	callout_stop(&sc->sc_wdtimer);
	callout_stop(&sc->sc_rftimer);

	iwi_stop_master(sc);

	CSR_WRITE_4(sc, IWI_CSR_RST, IWI_RST_SOFT_RESET);

	/* reset rings */
	iwi_reset_cmd_ring(sc, &sc->cmdq);
	iwi_reset_tx_ring(sc, &sc->txq[0]);
	iwi_reset_tx_ring(sc, &sc->txq[1]);
	iwi_reset_tx_ring(sc, &sc->txq[2]);
	iwi_reset_tx_ring(sc, &sc->txq[3]);
	iwi_reset_rx_ring(sc, &sc->rxq);

	sc->sc_tx_timer = 0;
	sc->sc_state_timer = 0;
	sc->sc_busy_timer = 0;
	sc->flags &= ~(IWI_FLAG_BUSY | IWI_FLAG_ASSOCIATED);
	sc->fw_state = IWI_FW_IDLE;
	wakeup(sc);
}