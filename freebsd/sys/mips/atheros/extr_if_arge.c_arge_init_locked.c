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
struct mii_data {int dummy; } ;
struct ifnet {int if_flags; int if_drv_flags; } ;
struct arge_softc {int arge_link_status; int /*<<< orphan*/  arge_stat_callout; scalar_t__ arge_miibus; int /*<<< orphan*/  arge_dev; struct ifnet* arge_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_DMA_INTR ; 
 int /*<<< orphan*/  AR71XX_DMA_RX_CONTROL ; 
 int /*<<< orphan*/  AR71XX_DMA_RX_DESC ; 
 int /*<<< orphan*/  AR71XX_DMA_TX_DESC ; 
 int /*<<< orphan*/  ARGE_LOCK_ASSERT (struct arge_softc*) ; 
 int /*<<< orphan*/  ARGE_RX_RING_ADDR (struct arge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARGE_TX_RING_ADDR (struct arge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARGE_WRITE (struct arge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_INTR_ALL ; 
 int /*<<< orphan*/  DMA_RX_CONTROL_EN ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  arge_reset_dma (struct arge_softc*) ; 
 scalar_t__ arge_rx_ring_init (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_stop (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_tick ; 
 int /*<<< orphan*/  arge_tx_ring_init (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_update_link_locked (struct arge_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arge_softc*) ; 
 struct mii_data* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static void
arge_init_locked(struct arge_softc *sc)
{
	struct ifnet		*ifp = sc->arge_ifp;
	struct mii_data		*mii;

	ARGE_LOCK_ASSERT(sc);

	if ((ifp->if_flags & IFF_UP) && (ifp->if_drv_flags & IFF_DRV_RUNNING))
		return;

	/* Init circular RX list. */
	if (arge_rx_ring_init(sc) != 0) {
		device_printf(sc->arge_dev,
		    "initialization failed: no memory for rx buffers\n");
		arge_stop(sc);
		return;
	}

	/* Init tx descriptors. */
	arge_tx_ring_init(sc);

	arge_reset_dma(sc);

	if (sc->arge_miibus) {
		mii = device_get_softc(sc->arge_miibus);
		mii_mediachg(mii);
	}
	else {
		/*
		 * Sun always shines over multiPHY interface
		 */
		sc->arge_link_status = 1;
	}

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	if (sc->arge_miibus) {
		callout_reset(&sc->arge_stat_callout, hz, arge_tick, sc);
		arge_update_link_locked(sc);
	}

	ARGE_WRITE(sc, AR71XX_DMA_TX_DESC, ARGE_TX_RING_ADDR(sc, 0));
	ARGE_WRITE(sc, AR71XX_DMA_RX_DESC, ARGE_RX_RING_ADDR(sc, 0));

	/* Start listening */
	ARGE_WRITE(sc, AR71XX_DMA_RX_CONTROL, DMA_RX_CONTROL_EN);

	/* Enable interrupts */
	ARGE_WRITE(sc, AR71XX_DMA_INTR, DMA_INTR_ALL);
}