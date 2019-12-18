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
struct are_txdesc {int /*<<< orphan*/ * tx_m; } ;
struct TYPE_3__ {int /*<<< orphan*/  are_tx_ring_map; int /*<<< orphan*/  are_tx_ring_tag; struct are_txdesc* are_txdesc; scalar_t__ are_tx_pkts; scalar_t__ are_tx_cnt; scalar_t__ are_tx_cons; scalar_t__ are_tx_prod; } ;
struct are_ring_data {TYPE_2__* are_tx_ring; } ;
struct are_softc {TYPE_1__ are_cdata; struct are_ring_data are_rdata; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  are_link; scalar_t__ are_addr; scalar_t__ are_devcs; scalar_t__ are_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARE_TX_RING_ADDR (struct are_softc*,int) ; 
 int ARE_TX_RING_CNT ; 
 int /*<<< orphan*/  ARE_TX_RING_SIZE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
are_tx_ring_init(struct are_softc *sc)
{
	struct are_ring_data	*rd;
	struct are_txdesc	*txd;
	bus_addr_t		addr;
	int			i;

	sc->are_cdata.are_tx_prod = 0;
	sc->are_cdata.are_tx_cons = 0;
	sc->are_cdata.are_tx_cnt = 0;
	sc->are_cdata.are_tx_pkts = 0;

	rd = &sc->are_rdata;
	bzero(rd->are_tx_ring, ARE_TX_RING_SIZE);
	for (i = 0; i < ARE_TX_RING_CNT; i++) {
		if (i == ARE_TX_RING_CNT - 1)
			addr = ARE_TX_RING_ADDR(sc, 0);
		else
			addr = ARE_TX_RING_ADDR(sc, i + 1);
		rd->are_tx_ring[i].are_stat = 0;
		rd->are_tx_ring[i].are_devcs = 0;
		rd->are_tx_ring[i].are_addr = 0;
		rd->are_tx_ring[i].are_link = addr;
		txd = &sc->are_cdata.are_txdesc[i];
		txd->tx_m = NULL;
	}

	bus_dmamap_sync(sc->are_cdata.are_tx_ring_tag,
	    sc->are_cdata.are_tx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}