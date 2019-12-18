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
struct vge_txdesc {int /*<<< orphan*/ * tx_desc; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_2__ {int /*<<< orphan*/  vge_tx_ring_map; int /*<<< orphan*/  vge_tx_ring_tag; struct vge_txdesc* vge_txdesc; scalar_t__ vge_tx_cnt; scalar_t__ vge_tx_considx; scalar_t__ vge_tx_prodidx; } ;
struct vge_ring_data {int /*<<< orphan*/ * vge_tx_ring; } ;
struct vge_softc {TYPE_1__ vge_cdata; struct vge_ring_data vge_rdata; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  VGE_LOCK_ASSERT (struct vge_softc*) ; 
 int VGE_TX_DESC_CNT ; 
 int /*<<< orphan*/  VGE_TX_LIST_SZ ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vge_tx_list_init(struct vge_softc *sc)
{
	struct vge_ring_data *rd;
	struct vge_txdesc *txd;
	int i;

	VGE_LOCK_ASSERT(sc);

	sc->vge_cdata.vge_tx_prodidx = 0;
	sc->vge_cdata.vge_tx_considx = 0;
	sc->vge_cdata.vge_tx_cnt = 0;

	rd = &sc->vge_rdata;
	bzero(rd->vge_tx_ring, VGE_TX_LIST_SZ);
	for (i = 0; i < VGE_TX_DESC_CNT; i++) {
		txd = &sc->vge_cdata.vge_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_desc = &rd->vge_tx_ring[i];
	}

	bus_dmamap_sync(sc->vge_cdata.vge_tx_ring_tag,
	    sc->vge_cdata.vge_tx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}