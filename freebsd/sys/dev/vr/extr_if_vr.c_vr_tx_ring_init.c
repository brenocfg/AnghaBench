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
struct vr_txdesc {int /*<<< orphan*/ * tx_m; } ;
struct TYPE_3__ {int /*<<< orphan*/  vr_tx_ring_map; int /*<<< orphan*/  vr_tx_ring_tag; struct vr_txdesc* vr_txdesc; scalar_t__ vr_tx_pkts; scalar_t__ vr_tx_cnt; scalar_t__ vr_tx_cons; scalar_t__ vr_tx_prod; } ;
struct vr_ring_data {TYPE_2__* vr_tx_ring; } ;
struct vr_softc {TYPE_1__ vr_cdata; struct vr_ring_data vr_rdata; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  vr_nextphys; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  VR_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VR_TX_RING_ADDR (struct vr_softc*,int) ; 
 int VR_TX_RING_CNT ; 
 int /*<<< orphan*/  VR_TX_RING_SIZE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vr_tx_ring_init(struct vr_softc *sc)
{
	struct vr_ring_data	*rd;
	struct vr_txdesc	*txd;
	bus_addr_t		addr;
	int			i;

	sc->vr_cdata.vr_tx_prod = 0;
	sc->vr_cdata.vr_tx_cons = 0;
	sc->vr_cdata.vr_tx_cnt = 0;
	sc->vr_cdata.vr_tx_pkts = 0;

	rd = &sc->vr_rdata;
	bzero(rd->vr_tx_ring, VR_TX_RING_SIZE);
	for (i = 0; i < VR_TX_RING_CNT; i++) {
		if (i == VR_TX_RING_CNT - 1)
			addr = VR_TX_RING_ADDR(sc, 0);
		else
			addr = VR_TX_RING_ADDR(sc, i + 1);
		rd->vr_tx_ring[i].vr_nextphys = htole32(VR_ADDR_LO(addr));
		txd = &sc->vr_cdata.vr_txdesc[i];
		txd->tx_m = NULL;
	}

	bus_dmamap_sync(sc->vr_cdata.vr_tx_ring_tag,
	    sc->vr_cdata.vr_tx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}