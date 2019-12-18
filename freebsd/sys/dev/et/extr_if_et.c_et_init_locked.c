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
struct et_softc {int /*<<< orphan*/  sc_tick; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_timer; struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_FLAG_LINK ; 
 int /*<<< orphan*/  ET_INTRS ; 
 int /*<<< orphan*/  ET_INTR_MASK ; 
 int /*<<< orphan*/  ET_LOCK_ASSERT (struct et_softc*) ; 
 int /*<<< orphan*/  ET_TIMER ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct et_softc*) ; 
 int et_chip_init (struct et_softc*) ; 
 int /*<<< orphan*/  et_ifmedia_upd_locked (struct ifnet*) ; 
 int et_init_rx_ring (struct et_softc*) ; 
 int /*<<< orphan*/  et_init_tx_ring (struct et_softc*) ; 
 int /*<<< orphan*/  et_reset (struct et_softc*) ; 
 int et_start_rxdma (struct et_softc*) ; 
 int et_start_txdma (struct et_softc*) ; 
 int /*<<< orphan*/  et_stop (struct et_softc*) ; 
 int /*<<< orphan*/  et_tick ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
et_init_locked(struct et_softc *sc)
{
	struct ifnet *ifp;
	int error;

	ET_LOCK_ASSERT(sc);

	ifp = sc->ifp;
	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	et_stop(sc);
	et_reset(sc);

	et_init_tx_ring(sc);
	error = et_init_rx_ring(sc);
	if (error)
		return;

	error = et_chip_init(sc);
	if (error)
		goto fail;

	/*
	 * Start TX/RX DMA engine
	 */
	error = et_start_rxdma(sc);
	if (error)
		return;

	error = et_start_txdma(sc);
	if (error)
		return;

	/* Enable interrupts. */
	CSR_WRITE_4(sc, ET_INTR_MASK, ~ET_INTRS);

	CSR_WRITE_4(sc, ET_TIMER, sc->sc_timer);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	sc->sc_flags &= ~ET_FLAG_LINK;
	et_ifmedia_upd_locked(ifp);

	callout_reset(&sc->sc_tick, hz, et_tick, sc);

fail:
	if (error)
		et_stop(sc);
}