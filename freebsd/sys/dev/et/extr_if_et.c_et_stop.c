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
struct ifnet {int if_drv_flags; } ;
struct et_softc {scalar_t__ watchdog_timer; int /*<<< orphan*/  sc_flags; scalar_t__ sc_tx_intr; scalar_t__ sc_tx; int /*<<< orphan*/  sc_tick; struct ifnet* ifp; } ;

/* Variables and functions */
 int CSR_READ_4 (struct et_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ET_FLAG_TXRX_ENABLED ; 
 int /*<<< orphan*/  ET_INTR_MASK ; 
 int /*<<< orphan*/  ET_LOCK_ASSERT (struct et_softc*) ; 
 int /*<<< orphan*/  ET_MAC_CFG1 ; 
 int ET_MAC_CFG1_RXEN ; 
 int ET_MAC_CFG1_TXEN ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  et_free_rx_ring (struct et_softc*) ; 
 int /*<<< orphan*/  et_free_tx_ring (struct et_softc*) ; 
 int /*<<< orphan*/  et_stats_update (struct et_softc*) ; 
 int /*<<< orphan*/  et_stop_rxdma (struct et_softc*) ; 
 int /*<<< orphan*/  et_stop_txdma (struct et_softc*) ; 

__attribute__((used)) static void
et_stop(struct et_softc *sc)
{
	struct ifnet *ifp;

	ET_LOCK_ASSERT(sc);

	ifp = sc->ifp;
	callout_stop(&sc->sc_tick);
	/* Disable interrupts. */
	CSR_WRITE_4(sc, ET_INTR_MASK, 0xffffffff);

	CSR_WRITE_4(sc, ET_MAC_CFG1, CSR_READ_4(sc, ET_MAC_CFG1) & ~(
	    ET_MAC_CFG1_TXEN | ET_MAC_CFG1_RXEN));
	DELAY(100);

	et_stop_rxdma(sc);
	et_stop_txdma(sc);
	et_stats_update(sc);

	et_free_tx_ring(sc);
	et_free_rx_ring(sc);

	sc->sc_tx = 0;
	sc->sc_tx_intr = 0;
	sc->sc_flags &= ~ET_FLAG_TXRX_ENABLED;

	sc->watchdog_timer = 0;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
}