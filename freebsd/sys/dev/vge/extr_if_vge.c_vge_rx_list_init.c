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
struct TYPE_2__ {scalar_t__ vge_rx_commit; int /*<<< orphan*/  vge_rx_ring_map; int /*<<< orphan*/  vge_rx_ring_tag; struct vge_rxdesc* vge_rxdesc; int /*<<< orphan*/ * vge_tail; int /*<<< orphan*/ * vge_head; scalar_t__ vge_rx_prodidx; } ;
struct vge_ring_data {int /*<<< orphan*/ * vge_rx_ring; } ;
struct vge_softc {TYPE_1__ vge_cdata; struct vge_ring_data vge_rdata; } ;
struct vge_rxdesc {struct vge_rxdesc* rxd_prev; int /*<<< orphan*/ * rx_desc; int /*<<< orphan*/ * rx_m; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  VGE_LOCK_ASSERT (struct vge_softc*) ; 
 int VGE_RX_DESC_CNT ; 
 int /*<<< orphan*/  VGE_RX_LIST_SZ ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vge_newbuf (struct vge_softc*,int) ; 

__attribute__((used)) static int
vge_rx_list_init(struct vge_softc *sc)
{
	struct vge_ring_data *rd;
	struct vge_rxdesc *rxd;
	int i;

	VGE_LOCK_ASSERT(sc);

	sc->vge_cdata.vge_rx_prodidx = 0;
	sc->vge_cdata.vge_head = NULL;
	sc->vge_cdata.vge_tail = NULL;
	sc->vge_cdata.vge_rx_commit = 0;

	rd = &sc->vge_rdata;
	bzero(rd->vge_rx_ring, VGE_RX_LIST_SZ);
	for (i = 0; i < VGE_RX_DESC_CNT; i++) {
		rxd = &sc->vge_cdata.vge_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_desc = &rd->vge_rx_ring[i];
		if (i == 0)
			rxd->rxd_prev =
			    &sc->vge_cdata.vge_rxdesc[VGE_RX_DESC_CNT - 1];
		else
			rxd->rxd_prev = &sc->vge_cdata.vge_rxdesc[i - 1];
		if (vge_newbuf(sc, i) != 0)
			return (ENOBUFS);
	}

	bus_dmamap_sync(sc->vge_cdata.vge_rx_ring_tag,
	    sc->vge_cdata.vge_rx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	sc->vge_cdata.vge_rx_commit = 0;

	return (0);
}