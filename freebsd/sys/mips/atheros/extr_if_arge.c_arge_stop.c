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
struct arge_softc {int /*<<< orphan*/  arge_stat_callout; scalar_t__ arge_miibus; struct ifnet* arge_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_DMA_INTR ; 
 int /*<<< orphan*/  ARGE_LOCK_ASSERT (struct arge_softc*) ; 
 int /*<<< orphan*/  ARGE_WRITE (struct arge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  arge_flush_ddr (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_reset_dma (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_rx_ring_free (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_tx_ring_free (struct arge_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arge_stop(struct arge_softc *sc)
{
	struct ifnet	    *ifp;

	ARGE_LOCK_ASSERT(sc);

	ifp = sc->arge_ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	if (sc->arge_miibus)
		callout_stop(&sc->arge_stat_callout);

	/* mask out interrupts */
	ARGE_WRITE(sc, AR71XX_DMA_INTR, 0);

	arge_reset_dma(sc);

	/* Flush FIFO and free any existing mbufs */
	arge_flush_ddr(sc);
	arge_rx_ring_free(sc);
	arge_tx_ring_free(sc);
}