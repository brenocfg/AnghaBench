#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ndis_softc {scalar_t__ ndis_txpending; size_t ndis_txidx; int ndis_tx_timer; TYPE_3__* ndis_chars; int /*<<< orphan*/ * ndis_tmaps; int /*<<< orphan*/  ndis_ttag; scalar_t__ ndis_sc; TYPE_4__** ndis_txarray; int /*<<< orphan*/  ndis_txpool; int /*<<< orphan*/  ndis_running; int /*<<< orphan*/  ndis_link; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct ndis_softc* ic_softc; } ;
struct TYPE_10__ {int /*<<< orphan*/ ** npe_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  npo_status; } ;
struct TYPE_12__ {size_t np_txidx; int /*<<< orphan*/  np_sclist; TYPE_2__ np_ext; TYPE_1__ np_oob; struct mbuf* np_m0; } ;
typedef  TYPE_4__ ndis_packet ;
struct TYPE_11__ {int /*<<< orphan*/ * nmc_sendmulti_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int ENOBUFS ; 
 int ENXIO ; 
 int /*<<< orphan*/  NDIS_INC (struct ndis_softc*) ; 
 int /*<<< orphan*/  NDIS_LOCK (struct ndis_softc*) ; 
 int /*<<< orphan*/  NDIS_STATUS_PENDING ; 
 int NDIS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  NDIS_UNLOCK (struct ndis_softc*) ; 
 int /*<<< orphan*/  NdisAllocatePacket (int*,TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_load_mbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndis_map_sclist ; 
 scalar_t__ ndis_mtop (struct mbuf*,TYPE_4__**) ; 
 size_t ndis_sclist_info ; 
 int /*<<< orphan*/  ndis_send_packet (struct ndis_softc*,TYPE_4__*) ; 
 int /*<<< orphan*/  ndis_send_packets (struct ndis_softc*,TYPE_4__**,int) ; 

__attribute__((used)) static int
ndis_80211transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct ndis_softc *sc = ic->ic_softc;
	ndis_packet **p0 = NULL, *p = NULL;
	int status;

	NDIS_LOCK(sc);
	if (!sc->ndis_link || !sc->ndis_running) {
		NDIS_UNLOCK(sc);
		return (ENXIO);
	}

	if (sc->ndis_txpending == 0) {
		NDIS_UNLOCK(sc);
		return (ENOBUFS);
	}

	p0 = &sc->ndis_txarray[sc->ndis_txidx];

	NdisAllocatePacket(&status,
	    &sc->ndis_txarray[sc->ndis_txidx], sc->ndis_txpool);

	if (status != NDIS_STATUS_SUCCESS) {
		NDIS_UNLOCK(sc);
		return (ENOBUFS);
	}

	if (ndis_mtop(m, &sc->ndis_txarray[sc->ndis_txidx])) {
		NDIS_UNLOCK(sc);
		return (ENOBUFS);
	}

	/*
	 * Save pointer to original mbuf
	 * so we can free it later.
	 */

	p = sc->ndis_txarray[sc->ndis_txidx];
	p->np_txidx = sc->ndis_txidx;
	p->np_m0 = m;
	p->np_oob.npo_status = NDIS_STATUS_PENDING;

	/*
	 * Do scatter/gather processing, if driver requested it.
	 */
	if (sc->ndis_sc) {
		bus_dmamap_load_mbuf(sc->ndis_ttag,
		    sc->ndis_tmaps[sc->ndis_txidx], m,
		    ndis_map_sclist, &p->np_sclist, BUS_DMA_NOWAIT);
		bus_dmamap_sync(sc->ndis_ttag,
		    sc->ndis_tmaps[sc->ndis_txidx],
		    BUS_DMASYNC_PREREAD);
		p->np_ext.npe_info[ndis_sclist_info] = &p->np_sclist;
	}

	NDIS_INC(sc);
	sc->ndis_txpending--;

	/*
	 * Set a timeout in case the chip goes out to lunch.
	 */
	sc->ndis_tx_timer = 5;
	NDIS_UNLOCK(sc);

	/*
	 * According to NDIS documentation, if a driver exports
	 * a MiniportSendPackets() routine, we prefer that over
	 * a MiniportSend() routine (which sends just a single
	 * packet).
	 */
	if (sc->ndis_chars->nmc_sendmulti_func != NULL)
		ndis_send_packets(sc, p0, 1);
	else
		ndis_send_packet(sc, p);

	return (0);
}