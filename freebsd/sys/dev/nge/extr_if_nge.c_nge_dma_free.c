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
struct nge_txdesc {int /*<<< orphan*/ * tx_dmamap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * nge_parent_tag; int /*<<< orphan*/ * nge_rx_tag; int /*<<< orphan*/ * nge_rx_sparemap; struct nge_rxdesc* nge_rxdesc; int /*<<< orphan*/ * nge_tx_tag; struct nge_txdesc* nge_txdesc; int /*<<< orphan*/ * nge_rx_ring_tag; int /*<<< orphan*/  nge_rx_ring_map; int /*<<< orphan*/ * nge_tx_ring_tag; int /*<<< orphan*/  nge_tx_ring_map; } ;
struct TYPE_3__ {scalar_t__ nge_rx_ring_paddr; int /*<<< orphan*/ * nge_rx_ring; scalar_t__ nge_tx_ring_paddr; int /*<<< orphan*/ * nge_tx_ring; } ;
struct nge_softc {TYPE_2__ nge_cdata; TYPE_1__ nge_rdata; } ;
struct nge_rxdesc {int /*<<< orphan*/ * rx_dmamap; } ;

/* Variables and functions */
 int NGE_RX_RING_CNT ; 
 int NGE_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nge_dma_free(struct nge_softc *sc)
{
	struct nge_txdesc *txd;
	struct nge_rxdesc *rxd;
	int i;

	/* Tx ring. */
	if (sc->nge_cdata.nge_tx_ring_tag) {
		if (sc->nge_rdata.nge_tx_ring_paddr)
			bus_dmamap_unload(sc->nge_cdata.nge_tx_ring_tag,
			    sc->nge_cdata.nge_tx_ring_map);
		if (sc->nge_rdata.nge_tx_ring)
			bus_dmamem_free(sc->nge_cdata.nge_tx_ring_tag,
			    sc->nge_rdata.nge_tx_ring,
			    sc->nge_cdata.nge_tx_ring_map);
		sc->nge_rdata.nge_tx_ring = NULL;
		sc->nge_rdata.nge_tx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->nge_cdata.nge_tx_ring_tag);
		sc->nge_cdata.nge_tx_ring_tag = NULL;
	}
	/* Rx ring. */
	if (sc->nge_cdata.nge_rx_ring_tag) {
		if (sc->nge_rdata.nge_rx_ring_paddr)
			bus_dmamap_unload(sc->nge_cdata.nge_rx_ring_tag,
			    sc->nge_cdata.nge_rx_ring_map);
		if (sc->nge_rdata.nge_rx_ring)
			bus_dmamem_free(sc->nge_cdata.nge_rx_ring_tag,
			    sc->nge_rdata.nge_rx_ring,
			    sc->nge_cdata.nge_rx_ring_map);
		sc->nge_rdata.nge_rx_ring = NULL;
		sc->nge_rdata.nge_rx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->nge_cdata.nge_rx_ring_tag);
		sc->nge_cdata.nge_rx_ring_tag = NULL;
	}
	/* Tx buffers. */
	if (sc->nge_cdata.nge_tx_tag) {
		for (i = 0; i < NGE_TX_RING_CNT; i++) {
			txd = &sc->nge_cdata.nge_txdesc[i];
			if (txd->tx_dmamap) {
				bus_dmamap_destroy(sc->nge_cdata.nge_tx_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = NULL;
			}
		}
		bus_dma_tag_destroy(sc->nge_cdata.nge_tx_tag);
		sc->nge_cdata.nge_tx_tag = NULL;
	}
	/* Rx buffers. */
	if (sc->nge_cdata.nge_rx_tag) {
		for (i = 0; i < NGE_RX_RING_CNT; i++) {
			rxd = &sc->nge_cdata.nge_rxdesc[i];
			if (rxd->rx_dmamap) {
				bus_dmamap_destroy(sc->nge_cdata.nge_rx_tag,
				    rxd->rx_dmamap);
				rxd->rx_dmamap = NULL;
			}
		}
		if (sc->nge_cdata.nge_rx_sparemap) {
			bus_dmamap_destroy(sc->nge_cdata.nge_rx_tag,
			    sc->nge_cdata.nge_rx_sparemap);
			sc->nge_cdata.nge_rx_sparemap = 0;
		}
		bus_dma_tag_destroy(sc->nge_cdata.nge_rx_tag);
		sc->nge_cdata.nge_rx_tag = NULL;
	}

	if (sc->nge_cdata.nge_parent_tag) {
		bus_dma_tag_destroy(sc->nge_cdata.nge_parent_tag);
		sc->nge_cdata.nge_parent_tag = NULL;
	}
}