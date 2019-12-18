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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct rx_rdesc {scalar_t__ status; scalar_t__ rdinfo; } ;
struct ifnet {int if_drv_flags; } ;
struct TYPE_4__ {int alc_rr_cons; scalar_t__ alc_rx_cons; int /*<<< orphan*/  alc_rx_ring_map; int /*<<< orphan*/  alc_rx_ring_tag; int /*<<< orphan*/  alc_rr_ring_map; int /*<<< orphan*/  alc_rr_ring_tag; } ;
struct TYPE_3__ {struct rx_rdesc* alc_rr_ring; } ;
struct alc_softc {int alc_flags; TYPE_2__ alc_cdata; int /*<<< orphan*/  alc_dev; TYPE_1__ alc_rdata; struct ifnet* alc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_DESC_INC (int,scalar_t__) ; 
 int ALC_FLAG_AR816X_FAMILY ; 
 int /*<<< orphan*/  ALC_MBOX_RD0_PROD_IDX ; 
 scalar_t__ ALC_RR_RING_CNT ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct alc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int EAGAIN ; 
 int EIO ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ RRD_RD_CNT (scalar_t__) ; 
 scalar_t__ RRD_VALID ; 
 int /*<<< orphan*/  alc_rxeof (struct alc_softc*,struct rx_rdesc*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ le32toh (scalar_t__) ; 

__attribute__((used)) static int
alc_rxintr(struct alc_softc *sc, int count)
{
	struct ifnet *ifp;
	struct rx_rdesc *rrd;
	uint32_t nsegs, status;
	int rr_cons, prog;

	bus_dmamap_sync(sc->alc_cdata.alc_rr_ring_tag,
	    sc->alc_cdata.alc_rr_ring_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	bus_dmamap_sync(sc->alc_cdata.alc_rx_ring_tag,
	    sc->alc_cdata.alc_rx_ring_map, BUS_DMASYNC_POSTWRITE);
	rr_cons = sc->alc_cdata.alc_rr_cons;
	ifp = sc->alc_ifp;
	for (prog = 0; (ifp->if_drv_flags & IFF_DRV_RUNNING) != 0;) {
		if (count-- <= 0)
			break;
		rrd = &sc->alc_rdata.alc_rr_ring[rr_cons];
		status = le32toh(rrd->status);
		if ((status & RRD_VALID) == 0)
			break;
		nsegs = RRD_RD_CNT(le32toh(rrd->rdinfo));
		if (nsegs == 0) {
			/* This should not happen! */
			device_printf(sc->alc_dev,
			    "unexpected segment count -- resetting\n");
			return (EIO);
		}
		alc_rxeof(sc, rrd);
		/* Clear Rx return status. */
		rrd->status = 0;
		ALC_DESC_INC(rr_cons, ALC_RR_RING_CNT);
		sc->alc_cdata.alc_rx_cons += nsegs;
		sc->alc_cdata.alc_rx_cons %= ALC_RR_RING_CNT;
		prog += nsegs;
	}

	if (prog > 0) {
		/* Update the consumer index. */
		sc->alc_cdata.alc_rr_cons = rr_cons;
		/* Sync Rx return descriptors. */
		bus_dmamap_sync(sc->alc_cdata.alc_rr_ring_tag,
		    sc->alc_cdata.alc_rr_ring_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		/*
		 * Sync updated Rx descriptors such that controller see
		 * modified buffer addresses.
		 */
		bus_dmamap_sync(sc->alc_cdata.alc_rx_ring_tag,
		    sc->alc_cdata.alc_rx_ring_map, BUS_DMASYNC_PREWRITE);
		/*
		 * Let controller know availability of new Rx buffers.
		 * Since alc(4) use RXQ_CFG_RD_BURST_DEFAULT descriptors
		 * it may be possible to update ALC_MBOX_RD0_PROD_IDX
		 * only when Rx buffer pre-fetching is required. In
		 * addition we already set ALC_RX_RD_FREE_THRESH to
		 * RX_RD_FREE_THRESH_LO_DEFAULT descriptors. However
		 * it still seems that pre-fetching needs more
		 * experimentation.
		 */
		if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) != 0)
			CSR_WRITE_2(sc, ALC_MBOX_RD0_PROD_IDX,
			    (uint16_t)sc->alc_cdata.alc_rx_cons);
		else
			CSR_WRITE_4(sc, ALC_MBOX_RD0_PROD_IDX,
			    sc->alc_cdata.alc_rx_cons);
	}

	return (count > 0 ? 0 : EAGAIN);
}