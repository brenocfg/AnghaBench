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
struct nge_txdesc {int /*<<< orphan*/ * tx_m; } ;
struct TYPE_3__ {int /*<<< orphan*/  nge_tx_ring_map; int /*<<< orphan*/  nge_tx_ring_tag; struct nge_txdesc* nge_txdesc; scalar_t__ nge_tx_cnt; scalar_t__ nge_tx_cons; scalar_t__ nge_tx_prod; } ;
struct nge_ring_data {TYPE_2__* nge_tx_ring; } ;
struct nge_softc {TYPE_1__ nge_cdata; struct nge_ring_data nge_rdata; } ;
struct nge_desc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  nge_next; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  NGE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGE_TX_RING_ADDR (struct nge_softc*,int) ; 
 int NGE_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nge_list_tx_init(struct nge_softc *sc)
{
	struct nge_ring_data *rd;
	struct nge_txdesc *txd;
	bus_addr_t addr;
	int i;

	sc->nge_cdata.nge_tx_prod = 0;
	sc->nge_cdata.nge_tx_cons = 0;
	sc->nge_cdata.nge_tx_cnt = 0;

	rd = &sc->nge_rdata;
	bzero(rd->nge_tx_ring, sizeof(struct nge_desc) * NGE_TX_RING_CNT);
	for (i = 0; i < NGE_TX_RING_CNT; i++) {
		if (i == NGE_TX_RING_CNT - 1)
			addr = NGE_TX_RING_ADDR(sc, 0);
		else
			addr = NGE_TX_RING_ADDR(sc, i + 1);
		rd->nge_tx_ring[i].nge_next = htole32(NGE_ADDR_LO(addr));
		txd = &sc->nge_cdata.nge_txdesc[i];
		txd->tx_m = NULL;
	}

	bus_dmamap_sync(sc->nge_cdata.nge_tx_ring_tag,
	    sc->nge_cdata.nge_tx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}