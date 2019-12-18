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
struct ffec_softc {size_t tx_idx_tail; size_t tx_idx_head; scalar_t__ tx_watchdog_count; int /*<<< orphan*/  txbuf_tag; struct ffec_bufmap* txbuf_map; struct ffec_hwdesc* txdesc_ring; struct ifnet* ifp; int /*<<< orphan*/  txdesc_map; int /*<<< orphan*/  txdesc_tag; } ;
struct ffec_hwdesc {int flags_len; } ;
struct ffec_bufmap {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  map; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int FEC_TXDESC_READY ; 
 int /*<<< orphan*/  FFEC_ASSERT_LOCKED (struct ffec_softc*) ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffec_setup_txdesc (struct ffec_softc*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffec_txstart_locked (struct ffec_softc*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 size_t next_txidx (struct ffec_softc*,size_t) ; 

__attribute__((used)) static void
ffec_txfinish_locked(struct ffec_softc *sc)
{
	struct ifnet *ifp;
	struct ffec_hwdesc *desc;
	struct ffec_bufmap *bmap;
	boolean_t retired_buffer;

	FFEC_ASSERT_LOCKED(sc);

	/* XXX Can't set PRE|POST right now, but we need both. */
	bus_dmamap_sync(sc->txdesc_tag, sc->txdesc_map, BUS_DMASYNC_PREREAD);
	bus_dmamap_sync(sc->txdesc_tag, sc->txdesc_map, BUS_DMASYNC_POSTREAD);
	ifp = sc->ifp;
	retired_buffer = false;
	while (sc->tx_idx_tail != sc->tx_idx_head) {
		desc = &sc->txdesc_ring[sc->tx_idx_tail];
		if (desc->flags_len & FEC_TXDESC_READY)
			break;
		retired_buffer = true;
		bmap = &sc->txbuf_map[sc->tx_idx_tail];
		bus_dmamap_sync(sc->txbuf_tag, bmap->map, 
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->txbuf_tag, bmap->map);
		m_freem(bmap->mbuf);
		bmap->mbuf = NULL;
		ffec_setup_txdesc(sc, sc->tx_idx_tail, 0, 0);
		sc->tx_idx_tail = next_txidx(sc, sc->tx_idx_tail);
	}

	/*
	 * If we retired any buffers, there will be open tx slots available in
	 * the descriptor ring, go try to start some new output.
	 */
	if (retired_buffer) {
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		ffec_txstart_locked(sc);
	}

	/* If there are no buffers outstanding, muzzle the watchdog. */
	if (sc->tx_idx_tail == sc->tx_idx_head) {
		sc->tx_watchdog_count = 0;
	}
}