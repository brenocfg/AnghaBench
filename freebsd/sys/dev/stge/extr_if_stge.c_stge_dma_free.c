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
struct stge_txdesc {scalar_t__ tx_dmamap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * stge_parent_tag; int /*<<< orphan*/ * stge_rx_tag; scalar_t__ stge_rx_sparemap; struct stge_rxdesc* stge_rxdesc; int /*<<< orphan*/ * stge_tx_tag; struct stge_txdesc* stge_txdesc; int /*<<< orphan*/ * stge_rx_ring_tag; int /*<<< orphan*/  stge_rx_ring_map; int /*<<< orphan*/ * stge_tx_ring_tag; int /*<<< orphan*/  stge_tx_ring_map; } ;
struct TYPE_3__ {scalar_t__ stge_rx_ring_paddr; int /*<<< orphan*/ * stge_rx_ring; scalar_t__ stge_tx_ring_paddr; int /*<<< orphan*/ * stge_tx_ring; } ;
struct stge_softc {TYPE_2__ sc_cdata; TYPE_1__ sc_rdata; } ;
struct stge_rxdesc {scalar_t__ rx_dmamap; } ;

/* Variables and functions */
 int STGE_RX_RING_CNT ; 
 int STGE_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
stge_dma_free(struct stge_softc *sc)
{
	struct stge_txdesc *txd;
	struct stge_rxdesc *rxd;
	int i;

	/* Tx ring */
	if (sc->sc_cdata.stge_tx_ring_tag) {
		if (sc->sc_rdata.stge_tx_ring_paddr)
			bus_dmamap_unload(sc->sc_cdata.stge_tx_ring_tag,
			    sc->sc_cdata.stge_tx_ring_map);
		if (sc->sc_rdata.stge_tx_ring)
			bus_dmamem_free(sc->sc_cdata.stge_tx_ring_tag,
			    sc->sc_rdata.stge_tx_ring,
			    sc->sc_cdata.stge_tx_ring_map);
		sc->sc_rdata.stge_tx_ring = NULL;
		sc->sc_rdata.stge_tx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->sc_cdata.stge_tx_ring_tag);
		sc->sc_cdata.stge_tx_ring_tag = NULL;
	}
	/* Rx ring */
	if (sc->sc_cdata.stge_rx_ring_tag) {
		if (sc->sc_rdata.stge_rx_ring_paddr)
			bus_dmamap_unload(sc->sc_cdata.stge_rx_ring_tag,
			    sc->sc_cdata.stge_rx_ring_map);
		if (sc->sc_rdata.stge_rx_ring)
			bus_dmamem_free(sc->sc_cdata.stge_rx_ring_tag,
			    sc->sc_rdata.stge_rx_ring,
			    sc->sc_cdata.stge_rx_ring_map);
		sc->sc_rdata.stge_rx_ring = NULL;
		sc->sc_rdata.stge_rx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->sc_cdata.stge_rx_ring_tag);
		sc->sc_cdata.stge_rx_ring_tag = NULL;
	}
	/* Tx buffers */
	if (sc->sc_cdata.stge_tx_tag) {
		for (i = 0; i < STGE_TX_RING_CNT; i++) {
			txd = &sc->sc_cdata.stge_txdesc[i];
			if (txd->tx_dmamap) {
				bus_dmamap_destroy(sc->sc_cdata.stge_tx_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = 0;
			}
		}
		bus_dma_tag_destroy(sc->sc_cdata.stge_tx_tag);
		sc->sc_cdata.stge_tx_tag = NULL;
	}
	/* Rx buffers */
	if (sc->sc_cdata.stge_rx_tag) {
		for (i = 0; i < STGE_RX_RING_CNT; i++) {
			rxd = &sc->sc_cdata.stge_rxdesc[i];
			if (rxd->rx_dmamap) {
				bus_dmamap_destroy(sc->sc_cdata.stge_rx_tag,
				    rxd->rx_dmamap);
				rxd->rx_dmamap = 0;
			}
		}
		if (sc->sc_cdata.stge_rx_sparemap) {
			bus_dmamap_destroy(sc->sc_cdata.stge_rx_tag,
			    sc->sc_cdata.stge_rx_sparemap);
			sc->sc_cdata.stge_rx_sparemap = 0;
		}
		bus_dma_tag_destroy(sc->sc_cdata.stge_rx_tag);
		sc->sc_cdata.stge_rx_tag = NULL;
	}

	if (sc->sc_cdata.stge_parent_tag) {
		bus_dma_tag_destroy(sc->sc_cdata.stge_parent_tag);
		sc->sc_cdata.stge_parent_tag = NULL;
	}
}