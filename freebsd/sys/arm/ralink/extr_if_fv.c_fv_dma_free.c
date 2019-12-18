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
struct fv_txdesc {int /*<<< orphan*/ * tx_dmamap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fv_parent_tag; int /*<<< orphan*/ * fv_rx_tag; int /*<<< orphan*/ * fv_rx_sparemap; struct fv_rxdesc* fv_rxdesc; int /*<<< orphan*/ * fv_tx_tag; struct fv_txdesc* fv_txdesc; int /*<<< orphan*/ * fv_rx_ring_tag; int /*<<< orphan*/  fv_rx_ring_map; int /*<<< orphan*/ * fv_tx_ring_tag; int /*<<< orphan*/  fv_tx_ring_map; } ;
struct TYPE_3__ {scalar_t__ fv_rx_ring_paddr; int /*<<< orphan*/ * fv_rx_ring; scalar_t__ fv_tx_ring_paddr; int /*<<< orphan*/ * fv_tx_ring; } ;
struct fv_softc {TYPE_2__ fv_cdata; TYPE_1__ fv_rdata; } ;
struct fv_rxdesc {int /*<<< orphan*/ * rx_dmamap; } ;

/* Variables and functions */
 int FV_RX_RING_CNT ; 
 int FV_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fv_dma_free(struct fv_softc *sc)
{
	struct fv_txdesc	*txd;
	struct fv_rxdesc	*rxd;
	int			i;

	/* Tx ring. */
	if (sc->fv_cdata.fv_tx_ring_tag) {
		if (sc->fv_rdata.fv_tx_ring_paddr)
			bus_dmamap_unload(sc->fv_cdata.fv_tx_ring_tag,
			    sc->fv_cdata.fv_tx_ring_map);
		if (sc->fv_rdata.fv_tx_ring)
			bus_dmamem_free(sc->fv_cdata.fv_tx_ring_tag,
			    sc->fv_rdata.fv_tx_ring,
			    sc->fv_cdata.fv_tx_ring_map);
		sc->fv_rdata.fv_tx_ring = NULL;
		sc->fv_rdata.fv_tx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->fv_cdata.fv_tx_ring_tag);
		sc->fv_cdata.fv_tx_ring_tag = NULL;
	}
	/* Rx ring. */
	if (sc->fv_cdata.fv_rx_ring_tag) {
		if (sc->fv_rdata.fv_rx_ring_paddr)
			bus_dmamap_unload(sc->fv_cdata.fv_rx_ring_tag,
			    sc->fv_cdata.fv_rx_ring_map);
		if (sc->fv_rdata.fv_rx_ring)
			bus_dmamem_free(sc->fv_cdata.fv_rx_ring_tag,
			    sc->fv_rdata.fv_rx_ring,
			    sc->fv_cdata.fv_rx_ring_map);
		sc->fv_rdata.fv_rx_ring = NULL;
		sc->fv_rdata.fv_rx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->fv_cdata.fv_rx_ring_tag);
		sc->fv_cdata.fv_rx_ring_tag = NULL;
	}
	/* Tx buffers. */
	if (sc->fv_cdata.fv_tx_tag) {
		for (i = 0; i < FV_TX_RING_CNT; i++) {
			txd = &sc->fv_cdata.fv_txdesc[i];
			if (txd->tx_dmamap) {
				bus_dmamap_destroy(sc->fv_cdata.fv_tx_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = NULL;
			}
		}
		bus_dma_tag_destroy(sc->fv_cdata.fv_tx_tag);
		sc->fv_cdata.fv_tx_tag = NULL;
	}
	/* Rx buffers. */
	if (sc->fv_cdata.fv_rx_tag) {
		for (i = 0; i < FV_RX_RING_CNT; i++) {
			rxd = &sc->fv_cdata.fv_rxdesc[i];
			if (rxd->rx_dmamap) {
				bus_dmamap_destroy(sc->fv_cdata.fv_rx_tag,
				    rxd->rx_dmamap);
				rxd->rx_dmamap = NULL;
			}
		}
		if (sc->fv_cdata.fv_rx_sparemap) {
			bus_dmamap_destroy(sc->fv_cdata.fv_rx_tag,
			    sc->fv_cdata.fv_rx_sparemap);
			sc->fv_cdata.fv_rx_sparemap = 0;
		}
		bus_dma_tag_destroy(sc->fv_cdata.fv_rx_tag);
		sc->fv_cdata.fv_rx_tag = NULL;
	}

	if (sc->fv_cdata.fv_parent_tag) {
		bus_dma_tag_destroy(sc->fv_cdata.fv_parent_tag);
		sc->fv_cdata.fv_parent_tag = NULL;
	}
}