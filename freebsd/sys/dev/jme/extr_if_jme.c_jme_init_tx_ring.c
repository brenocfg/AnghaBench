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
struct jme_txdesc {scalar_t__ tx_ndesc; int /*<<< orphan*/ * tx_desc; int /*<<< orphan*/ * tx_m; } ;
struct TYPE_2__ {int /*<<< orphan*/  jme_tx_ring_map; int /*<<< orphan*/  jme_tx_ring_tag; struct jme_txdesc* jme_txdesc; scalar_t__ jme_tx_cnt; scalar_t__ jme_tx_cons; scalar_t__ jme_tx_prod; } ;
struct jme_ring_data {int /*<<< orphan*/ * jme_tx_ring; } ;
struct jme_softc {TYPE_1__ jme_cdata; struct jme_ring_data jme_rdata; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int JME_TX_RING_CNT ; 
 int /*<<< orphan*/  JME_TX_RING_SIZE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
jme_init_tx_ring(struct jme_softc *sc)
{
	struct jme_ring_data *rd;
	struct jme_txdesc *txd;
	int i;

	sc->jme_cdata.jme_tx_prod = 0;
	sc->jme_cdata.jme_tx_cons = 0;
	sc->jme_cdata.jme_tx_cnt = 0;

	rd = &sc->jme_rdata;
	bzero(rd->jme_tx_ring, JME_TX_RING_SIZE);
	for (i = 0; i < JME_TX_RING_CNT; i++) {
		txd = &sc->jme_cdata.jme_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_desc = &rd->jme_tx_ring[i];
		txd->tx_ndesc = 0;
	}

	bus_dmamap_sync(sc->jme_cdata.jme_tx_ring_tag,
	    sc->jme_cdata.jme_tx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
}