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
struct ti_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct TYPE_4__ {int /*<<< orphan*/  ti_tx_ring_map; int /*<<< orphan*/  ti_tx_ring_tag; int /*<<< orphan*/  ti_tx_tag; struct ti_txdesc* ti_txdesc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ti_tx_ring; } ;
struct ti_softc {TYPE_2__ ti_cdata; TYPE_1__ ti_rdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int TI_TX_RING_CNT ; 
 int /*<<< orphan*/  TI_TX_RING_SZ ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ti_free_tx_ring(struct ti_softc *sc)
{
	struct ti_txdesc *txd;
	int i;

	if (sc->ti_rdata.ti_tx_ring == NULL)
		return;

	for (i = 0; i < TI_TX_RING_CNT; i++) {
		txd = &sc->ti_cdata.ti_txdesc[i];
		if (txd->tx_m != NULL) {
			bus_dmamap_sync(sc->ti_cdata.ti_tx_tag, txd->tx_dmamap,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->ti_cdata.ti_tx_tag,
			    txd->tx_dmamap);
			m_freem(txd->tx_m);
			txd->tx_m = NULL;
		}
	}
	bzero(sc->ti_rdata.ti_tx_ring, TI_TX_RING_SZ);
	bus_dmamap_sync(sc->ti_cdata.ti_tx_ring_tag,
	    sc->ti_cdata.ti_tx_ring_map, BUS_DMASYNC_PREWRITE);
}