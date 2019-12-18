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
struct rt2560_softc {int sc_flags; int /*<<< orphan*/  rxq; int /*<<< orphan*/  bcnq; int /*<<< orphan*/  prioq; int /*<<< orphan*/  atimq; int /*<<< orphan*/  txq; scalar_t__ sc_tx_timer; int /*<<< orphan*/  watchdog_ch; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK_ASSERT (struct rt2560_softc*) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2560_ABORT_TX ; 
 int /*<<< orphan*/  RT2560_CSR1 ; 
 int /*<<< orphan*/  RT2560_CSR8 ; 
 int RT2560_DISABLE_RX ; 
 int volatile RT2560_F_INPUT_RUNNING ; 
 int RT2560_F_RUNNING ; 
 int RT2560_RESET_ASIC ; 
 int /*<<< orphan*/  RT2560_RXCSR0 ; 
 int /*<<< orphan*/  RT2560_TXCSR0 ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  msleep (struct rt2560_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rt2560_reset_rx_ring (struct rt2560_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2560_reset_tx_ring (struct rt2560_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt2560_stop_locked(struct rt2560_softc *sc)
{
	volatile int *flags = &sc->sc_flags;

	RAL_LOCK_ASSERT(sc);

	while (*flags & RT2560_F_INPUT_RUNNING)
		msleep(sc, &sc->sc_mtx, 0, "ralrunning", hz/10);

	callout_stop(&sc->watchdog_ch);
	sc->sc_tx_timer = 0;

	if (sc->sc_flags & RT2560_F_RUNNING) {
		sc->sc_flags &= ~RT2560_F_RUNNING;

		/* abort Tx */
		RAL_WRITE(sc, RT2560_TXCSR0, RT2560_ABORT_TX);
		
		/* disable Rx */
		RAL_WRITE(sc, RT2560_RXCSR0, RT2560_DISABLE_RX);

		/* reset ASIC (imply reset BBP) */
		RAL_WRITE(sc, RT2560_CSR1, RT2560_RESET_ASIC);
		RAL_WRITE(sc, RT2560_CSR1, 0);

		/* disable interrupts */
		RAL_WRITE(sc, RT2560_CSR8, 0xffffffff);
		
		/* reset Tx and Rx rings */
		rt2560_reset_tx_ring(sc, &sc->txq);
		rt2560_reset_tx_ring(sc, &sc->atimq);
		rt2560_reset_tx_ring(sc, &sc->prioq);
		rt2560_reset_tx_ring(sc, &sc->bcnq);
		rt2560_reset_rx_ring(sc, &sc->rxq);
	}
}