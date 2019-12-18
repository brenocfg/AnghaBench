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
typedef  int uint32_t ;
struct rt2661_softc {int sc_flags; int /*<<< orphan*/  rxq; int /*<<< orphan*/  mgtq; int /*<<< orphan*/ * txq; scalar_t__ sc_tx_timer; int /*<<< orphan*/  watchdog_ch; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int volatile RAL_INPUT_RUNNING ; 
 int RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int RAL_RUNNING ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2661_DISABLE_RX ; 
 int /*<<< orphan*/  RT2661_INT_MASK_CSR ; 
 int /*<<< orphan*/  RT2661_INT_SOURCE_CSR ; 
 int /*<<< orphan*/  RT2661_MAC_CSR1 ; 
 int /*<<< orphan*/  RT2661_MCU_INT_MASK_CSR ; 
 int /*<<< orphan*/  RT2661_MCU_INT_SOURCE_CSR ; 
 int /*<<< orphan*/  RT2661_TXRX_CSR0 ; 
 int /*<<< orphan*/  RT2661_TX_CNTL_CSR ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  msleep (struct rt2661_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rt2661_reset_rx_ring (struct rt2661_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2661_reset_tx_ring (struct rt2661_softc*,int /*<<< orphan*/ *) ; 

void
rt2661_stop_locked(struct rt2661_softc *sc)
{
	volatile int *flags = &sc->sc_flags;
	uint32_t tmp;

	while (*flags & RAL_INPUT_RUNNING)
		msleep(sc, &sc->sc_mtx, 0, "ralrunning", hz/10);

	callout_stop(&sc->watchdog_ch);
	sc->sc_tx_timer = 0;

	if (sc->sc_flags & RAL_RUNNING) {
		sc->sc_flags &= ~RAL_RUNNING;

		/* abort Tx (for all 5 Tx rings) */
		RAL_WRITE(sc, RT2661_TX_CNTL_CSR, 0x1f << 16);
		
		/* disable Rx (value remains after reset!) */
		tmp = RAL_READ(sc, RT2661_TXRX_CSR0);
		RAL_WRITE(sc, RT2661_TXRX_CSR0, tmp | RT2661_DISABLE_RX);
		
		/* reset ASIC */
		RAL_WRITE(sc, RT2661_MAC_CSR1, 3);
		RAL_WRITE(sc, RT2661_MAC_CSR1, 0);
		
		/* disable interrupts */
		RAL_WRITE(sc, RT2661_INT_MASK_CSR, 0xffffffff);
		RAL_WRITE(sc, RT2661_MCU_INT_MASK_CSR, 0xffffffff);
		
		/* clear any pending interrupt */
		RAL_WRITE(sc, RT2661_INT_SOURCE_CSR, 0xffffffff);
		RAL_WRITE(sc, RT2661_MCU_INT_SOURCE_CSR, 0xffffffff);
		
		/* reset Tx and Rx rings */
		rt2661_reset_tx_ring(sc, &sc->txq[0]);
		rt2661_reset_tx_ring(sc, &sc->txq[1]);
		rt2661_reset_tx_ring(sc, &sc->txq[2]);
		rt2661_reset_tx_ring(sc, &sc->txq[3]);
		rt2661_reset_tx_ring(sc, &sc->mgtq);
		rt2661_reset_rx_ring(sc, &sc->rxq);
	}
}