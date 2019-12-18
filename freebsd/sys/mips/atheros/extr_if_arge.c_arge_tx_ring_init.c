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
struct arge_txdesc {int /*<<< orphan*/ * tx_m; } ;
struct TYPE_3__ {int /*<<< orphan*/  arge_tx_ring_map; int /*<<< orphan*/  arge_tx_ring_tag; struct arge_txdesc* arge_txdesc; scalar_t__ arge_tx_cnt; scalar_t__ arge_tx_cons; scalar_t__ arge_tx_prod; } ;
struct arge_ring_data {TYPE_2__* arge_tx_ring; } ;
struct arge_softc {TYPE_1__ arge_cdata; struct arge_ring_data arge_rdata; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  next_desc; int /*<<< orphan*/  packet_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARGE_DESC_EMPTY ; 
 int /*<<< orphan*/  ARGE_TX_RING_ADDR (struct arge_softc*,int) ; 
 int ARGE_TX_RING_COUNT ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 

__attribute__((used)) static int
arge_tx_ring_init(struct arge_softc *sc)
{
	struct arge_ring_data	*rd;
	struct arge_txdesc	*txd;
	bus_addr_t		addr;
	int			i;

	sc->arge_cdata.arge_tx_prod = 0;
	sc->arge_cdata.arge_tx_cons = 0;
	sc->arge_cdata.arge_tx_cnt = 0;

	rd = &sc->arge_rdata;
	bzero(rd->arge_tx_ring, sizeof(*rd->arge_tx_ring));
	for (i = 0; i < ARGE_TX_RING_COUNT; i++) {
		if (i == ARGE_TX_RING_COUNT - 1)
			addr = ARGE_TX_RING_ADDR(sc, 0);
		else
			addr = ARGE_TX_RING_ADDR(sc, i + 1);
		rd->arge_tx_ring[i].packet_ctrl = ARGE_DESC_EMPTY;
		rd->arge_tx_ring[i].next_desc = addr;
		txd = &sc->arge_cdata.arge_txdesc[i];
		txd->tx_m = NULL;
	}

	bus_dmamap_sync(sc->arge_cdata.arge_tx_ring_tag,
	    sc->arge_cdata.arge_tx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}