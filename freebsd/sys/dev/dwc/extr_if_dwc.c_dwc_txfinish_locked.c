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
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct dwc_softc {size_t tx_idx_tail; size_t tx_idx_head; scalar_t__ tx_watchdog_count; int /*<<< orphan*/  txbuf_tag; struct dwc_bufmap* txbuf_map; struct dwc_hwdesc* txdesc_ring; struct ifnet* ifp; } ;
struct dwc_hwdesc {int tdes0; } ;
struct dwc_bufmap {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int DDESC_TDES0_OWN ; 
 int /*<<< orphan*/  DWC_ASSERT_LOCKED (struct dwc_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_setup_txdesc (struct dwc_softc*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 size_t next_txidx (struct dwc_softc*,size_t) ; 

__attribute__((used)) static void
dwc_txfinish_locked(struct dwc_softc *sc)
{
	struct dwc_bufmap *bmap;
	struct dwc_hwdesc *desc;
	struct ifnet *ifp;

	DWC_ASSERT_LOCKED(sc);

	ifp = sc->ifp;
	while (sc->tx_idx_tail != sc->tx_idx_head) {
		desc = &sc->txdesc_ring[sc->tx_idx_tail];
		if ((desc->tdes0 & DDESC_TDES0_OWN) != 0)
			break;
		bmap = &sc->txbuf_map[sc->tx_idx_tail];
		bus_dmamap_sync(sc->txbuf_tag, bmap->map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->txbuf_tag, bmap->map);
		m_freem(bmap->mbuf);
		bmap->mbuf = NULL;
		dwc_setup_txdesc(sc, sc->tx_idx_tail, 0, 0);
		sc->tx_idx_tail = next_txidx(sc, sc->tx_idx_tail);
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
	}

	/* If there are no buffers outstanding, muzzle the watchdog. */
	if (sc->tx_idx_tail == sc->tx_idx_head) {
		sc->tx_watchdog_count = 0;
	}
}