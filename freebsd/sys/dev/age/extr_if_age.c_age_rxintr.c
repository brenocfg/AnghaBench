#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rx_rdesc {scalar_t__ index; scalar_t__ len; } ;
struct TYPE_4__ {int age_rr_cons; int age_rx_cons; int /*<<< orphan*/  age_rr_ring_map; int /*<<< orphan*/  age_rr_ring_tag; int /*<<< orphan*/  age_rx_ring_map; int /*<<< orphan*/  age_rx_ring_tag; } ;
struct TYPE_3__ {struct rx_rdesc* age_rr_ring; } ;
struct age_softc {TYPE_2__ age_cdata; TYPE_1__ age_rdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_COMMIT_MBOX (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_DESC_INC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AGE_LOCK_ASSERT (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_RR_RING_CNT ; 
 int /*<<< orphan*/  AGE_RX_BUF_SIZE ; 
 int AGE_RX_BYTES (int /*<<< orphan*/ ) ; 
 int AGE_RX_NSEGS (int /*<<< orphan*/ ) ; 
 int AGE_RX_RING_CNT ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  age_rxeof (struct age_softc*,struct rx_rdesc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (scalar_t__) ; 

__attribute__((used)) static int
age_rxintr(struct age_softc *sc, int rr_prod, int count)
{
	struct rx_rdesc *rxrd;
	int rr_cons, nsegs, pktlen, prog;

	AGE_LOCK_ASSERT(sc);

	rr_cons = sc->age_cdata.age_rr_cons;
	if (rr_cons == rr_prod)
		return (0);

	bus_dmamap_sync(sc->age_cdata.age_rr_ring_tag,
	    sc->age_cdata.age_rr_ring_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	bus_dmamap_sync(sc->age_cdata.age_rx_ring_tag,
	    sc->age_cdata.age_rx_ring_map, BUS_DMASYNC_POSTWRITE);

	for (prog = 0; rr_cons != rr_prod; prog++) {
		if (count-- <= 0)
			break;
		rxrd = &sc->age_rdata.age_rr_ring[rr_cons];
		nsegs = AGE_RX_NSEGS(le32toh(rxrd->index));
		if (nsegs == 0)
			break;
		/*
		 * Check number of segments against received bytes.
		 * Non-matching value would indicate that hardware
		 * is still trying to update Rx return descriptors.
		 * I'm not sure whether this check is really needed.
		 */
		pktlen = AGE_RX_BYTES(le32toh(rxrd->len));
		if (nsegs != howmany(pktlen, AGE_RX_BUF_SIZE))
			break;

		/* Received a frame. */
		age_rxeof(sc, rxrd);
		/* Clear return ring. */
		rxrd->index = 0;
		AGE_DESC_INC(rr_cons, AGE_RR_RING_CNT);
		sc->age_cdata.age_rx_cons += nsegs;
		sc->age_cdata.age_rx_cons %= AGE_RX_RING_CNT;
	}

	if (prog > 0) {
		/* Update the consumer index. */
		sc->age_cdata.age_rr_cons = rr_cons;

		bus_dmamap_sync(sc->age_cdata.age_rx_ring_tag,
		    sc->age_cdata.age_rx_ring_map, BUS_DMASYNC_PREWRITE);
		/* Sync descriptors. */
		bus_dmamap_sync(sc->age_cdata.age_rr_ring_tag,
		    sc->age_cdata.age_rr_ring_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

		/* Notify hardware availability of new Rx buffers. */
		AGE_COMMIT_MBOX(sc);
	}

	return (count > 0 ? 0 : EAGAIN);
}