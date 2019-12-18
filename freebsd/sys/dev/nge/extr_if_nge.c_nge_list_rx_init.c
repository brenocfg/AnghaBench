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
struct TYPE_3__ {int /*<<< orphan*/  nge_rx_ring_map; int /*<<< orphan*/  nge_rx_ring_tag; scalar_t__ nge_rx_cons; } ;
struct nge_ring_data {TYPE_2__* nge_rx_ring; } ;
struct nge_softc {TYPE_1__ nge_cdata; struct nge_ring_data nge_rdata; int /*<<< orphan*/ * nge_tail; int /*<<< orphan*/  nge_head; } ;
struct nge_desc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  nge_next; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NGE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGE_RX_RING_ADDR (struct nge_softc*,int) ; 
 int NGE_RX_RING_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 scalar_t__ nge_newbuf (struct nge_softc*,int) ; 

__attribute__((used)) static int
nge_list_rx_init(struct nge_softc *sc)
{
	struct nge_ring_data *rd;
	bus_addr_t addr;
	int i;

	sc->nge_cdata.nge_rx_cons = 0;
	sc->nge_head = sc->nge_tail = NULL;

	rd = &sc->nge_rdata;
	bzero(rd->nge_rx_ring, sizeof(struct nge_desc) * NGE_RX_RING_CNT);
	for (i = 0; i < NGE_RX_RING_CNT; i++) {
		if (nge_newbuf(sc, i) != 0)
			return (ENOBUFS);
		if (i == NGE_RX_RING_CNT - 1)
			addr = NGE_RX_RING_ADDR(sc, 0);
		else
			addr = NGE_RX_RING_ADDR(sc, i + 1);
		rd->nge_rx_ring[i].nge_next = htole32(NGE_ADDR_LO(addr));
	}

	bus_dmamap_sync(sc->nge_cdata.nge_rx_ring_tag,
	    sc->nge_cdata.nge_rx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}