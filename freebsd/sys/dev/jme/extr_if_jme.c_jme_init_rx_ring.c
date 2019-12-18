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
struct TYPE_2__ {int /*<<< orphan*/  jme_rx_ring_map; int /*<<< orphan*/  jme_rx_ring_tag; struct jme_rxdesc* jme_rxdesc; scalar_t__ jme_rx_cons; } ;
struct jme_ring_data {int /*<<< orphan*/ * jme_rx_ring; } ;
struct jme_softc {TYPE_1__ jme_cdata; struct jme_ring_data jme_rdata; scalar_t__ jme_morework; } ;
struct jme_rxdesc {int /*<<< orphan*/ * rx_desc; int /*<<< orphan*/ * rx_m; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  JME_RXCHAIN_RESET (struct jme_softc*) ; 
 int JME_RX_RING_CNT ; 
 int /*<<< orphan*/  JME_RX_RING_SIZE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jme_newbuf (struct jme_softc*,struct jme_rxdesc*) ; 

__attribute__((used)) static int
jme_init_rx_ring(struct jme_softc *sc)
{
	struct jme_ring_data *rd;
	struct jme_rxdesc *rxd;
	int i;

	sc->jme_cdata.jme_rx_cons = 0;
	JME_RXCHAIN_RESET(sc);
	sc->jme_morework = 0;

	rd = &sc->jme_rdata;
	bzero(rd->jme_rx_ring, JME_RX_RING_SIZE);
	for (i = 0; i < JME_RX_RING_CNT; i++) {
		rxd = &sc->jme_cdata.jme_rxdesc[i];
		rxd->rx_m = NULL;
		rxd->rx_desc = &rd->jme_rx_ring[i];
		if (jme_newbuf(sc, rxd) != 0)
			return (ENOBUFS);
	}

	bus_dmamap_sync(sc->jme_cdata.jme_rx_ring_tag,
	    sc->jme_cdata.jme_rx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}