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
struct TYPE_3__ {int /*<<< orphan*/  are_rx_ring_map; int /*<<< orphan*/  are_rx_ring_tag; struct are_rxdesc* are_rxdesc; scalar_t__ are_rx_cons; } ;
struct are_ring_data {TYPE_2__* are_rx_ring; } ;
struct are_softc {TYPE_1__ are_cdata; struct are_ring_data are_rdata; } ;
struct are_rxdesc {TYPE_2__* desc; int /*<<< orphan*/ * rx_m; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  are_link; scalar_t__ are_addr; int /*<<< orphan*/  are_devcs; int /*<<< orphan*/  are_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADCTL_CH ; 
 int /*<<< orphan*/  ADCTL_ER ; 
 int /*<<< orphan*/  ADSTAT_OWN ; 
 int /*<<< orphan*/  ARE_RX_RING_ADDR (struct are_softc*,int) ; 
 int ARE_RX_RING_CNT ; 
 int /*<<< orphan*/  ARE_RX_RING_SIZE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOBUFS ; 
 scalar_t__ are_newbuf (struct are_softc*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
are_rx_ring_init(struct are_softc *sc)
{
	struct are_ring_data	*rd;
	struct are_rxdesc	*rxd;
	bus_addr_t		addr;
	int			i;

	sc->are_cdata.are_rx_cons = 0;

	rd = &sc->are_rdata;
	bzero(rd->are_rx_ring, ARE_RX_RING_SIZE);
	for (i = 0; i < ARE_RX_RING_CNT; i++) {
		rxd = &sc->are_cdata.are_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->desc = &rd->are_rx_ring[i];
		if (i == ARE_RX_RING_CNT - 1)
			addr = ARE_RX_RING_ADDR(sc, 0);
		else
			addr = ARE_RX_RING_ADDR(sc, i + 1);
		rd->are_rx_ring[i].are_stat = ADSTAT_OWN;
		rd->are_rx_ring[i].are_devcs = ADCTL_CH;
		if (i == ARE_RX_RING_CNT - 1)
			rd->are_rx_ring[i].are_devcs |= ADCTL_ER;
		rd->are_rx_ring[i].are_addr = 0;
		rd->are_rx_ring[i].are_link = addr;
		if (are_newbuf(sc, i) != 0)
			return (ENOBUFS);
	}

	bus_dmamap_sync(sc->are_cdata.are_rx_ring_tag,
	    sc->are_cdata.are_rx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}