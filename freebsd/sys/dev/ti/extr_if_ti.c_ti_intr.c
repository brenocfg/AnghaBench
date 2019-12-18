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
struct TYPE_2__ {int /*<<< orphan*/  ti_status_map; int /*<<< orphan*/  ti_status_tag; } ;
struct ti_softc {TYPE_1__ ti_cdata; struct ifnet* ti_ifp; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int CSR_READ_4 (struct ti_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ti_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TI_LOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_MB_HOSTINTR ; 
 int TI_MHC_INTSTATE ; 
 int /*<<< orphan*/  TI_MISC_HOST_CTL ; 
 int /*<<< orphan*/  TI_UNLOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_handle_events (struct ti_softc*) ; 
 int /*<<< orphan*/  ti_rxeof (struct ti_softc*) ; 
 int /*<<< orphan*/  ti_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  ti_txeof (struct ti_softc*) ; 

__attribute__((used)) static void
ti_intr(void *xsc)
{
	struct ti_softc *sc;
	struct ifnet *ifp;

	sc = xsc;
	TI_LOCK(sc);
	ifp = sc->ti_ifp;

	/* Make sure this is really our interrupt. */
	if (!(CSR_READ_4(sc, TI_MISC_HOST_CTL) & TI_MHC_INTSTATE)) {
		TI_UNLOCK(sc);
		return;
	}

	/* Ack interrupt and stop others from occurring. */
	CSR_WRITE_4(sc, TI_MB_HOSTINTR, 1);

	if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
		bus_dmamap_sync(sc->ti_cdata.ti_status_tag,
		    sc->ti_cdata.ti_status_map, BUS_DMASYNC_POSTREAD);
		/* Check RX return ring producer/consumer */
		ti_rxeof(sc);

		/* Check TX ring producer/consumer */
		ti_txeof(sc);
		bus_dmamap_sync(sc->ti_cdata.ti_status_tag,
		    sc->ti_cdata.ti_status_map, BUS_DMASYNC_PREREAD);
	}

	ti_handle_events(sc);

	if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
		/* Re-enable interrupts. */
		CSR_WRITE_4(sc, TI_MB_HOSTINTR, 0);
		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			ti_start_locked(ifp);
	}

	TI_UNLOCK(sc);
}