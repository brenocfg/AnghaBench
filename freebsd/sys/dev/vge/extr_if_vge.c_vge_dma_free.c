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
struct vge_txdesc {int /*<<< orphan*/ * tx_dmamap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vge_ring_tag; int /*<<< orphan*/ * vge_buffer_tag; int /*<<< orphan*/ * vge_rx_tag; int /*<<< orphan*/ * vge_rx_sparemap; struct vge_rxdesc* vge_rxdesc; int /*<<< orphan*/ * vge_tx_tag; struct vge_txdesc* vge_txdesc; int /*<<< orphan*/ * vge_rx_ring_tag; int /*<<< orphan*/  vge_rx_ring_map; int /*<<< orphan*/ * vge_tx_ring_tag; int /*<<< orphan*/  vge_tx_ring_map; } ;
struct TYPE_3__ {scalar_t__ vge_rx_ring_paddr; int /*<<< orphan*/ * vge_rx_ring; scalar_t__ vge_tx_ring_paddr; int /*<<< orphan*/ * vge_tx_ring; } ;
struct vge_softc {TYPE_2__ vge_cdata; TYPE_1__ vge_rdata; } ;
struct vge_rxdesc {int /*<<< orphan*/ * rx_dmamap; } ;

/* Variables and functions */
 int VGE_RX_DESC_CNT ; 
 int VGE_TX_DESC_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vge_dma_free(struct vge_softc *sc)
{
	struct vge_txdesc *txd;
	struct vge_rxdesc *rxd;
	int i;

	/* Tx ring. */
	if (sc->vge_cdata.vge_tx_ring_tag != NULL) {
		if (sc->vge_rdata.vge_tx_ring_paddr)
			bus_dmamap_unload(sc->vge_cdata.vge_tx_ring_tag,
			    sc->vge_cdata.vge_tx_ring_map);
		if (sc->vge_rdata.vge_tx_ring)
			bus_dmamem_free(sc->vge_cdata.vge_tx_ring_tag,
			    sc->vge_rdata.vge_tx_ring,
			    sc->vge_cdata.vge_tx_ring_map);
		sc->vge_rdata.vge_tx_ring = NULL;
		sc->vge_rdata.vge_tx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->vge_cdata.vge_tx_ring_tag);
		sc->vge_cdata.vge_tx_ring_tag = NULL;
	}
	/* Rx ring. */
	if (sc->vge_cdata.vge_rx_ring_tag != NULL) {
		if (sc->vge_rdata.vge_rx_ring_paddr)
			bus_dmamap_unload(sc->vge_cdata.vge_rx_ring_tag,
			    sc->vge_cdata.vge_rx_ring_map);
		if (sc->vge_rdata.vge_rx_ring)
			bus_dmamem_free(sc->vge_cdata.vge_rx_ring_tag,
			    sc->vge_rdata.vge_rx_ring,
			    sc->vge_cdata.vge_rx_ring_map);
		sc->vge_rdata.vge_rx_ring = NULL;
		sc->vge_rdata.vge_rx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->vge_cdata.vge_rx_ring_tag);
		sc->vge_cdata.vge_rx_ring_tag = NULL;
	}
	/* Tx buffers. */
	if (sc->vge_cdata.vge_tx_tag != NULL) {
		for (i = 0; i < VGE_TX_DESC_CNT; i++) {
			txd = &sc->vge_cdata.vge_txdesc[i];
			if (txd->tx_dmamap != NULL) {
				bus_dmamap_destroy(sc->vge_cdata.vge_tx_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = NULL;
			}
		}
		bus_dma_tag_destroy(sc->vge_cdata.vge_tx_tag);
		sc->vge_cdata.vge_tx_tag = NULL;
	}
	/* Rx buffers. */
	if (sc->vge_cdata.vge_rx_tag != NULL) {
		for (i = 0; i < VGE_RX_DESC_CNT; i++) {
			rxd = &sc->vge_cdata.vge_rxdesc[i];
			if (rxd->rx_dmamap != NULL) {
				bus_dmamap_destroy(sc->vge_cdata.vge_rx_tag,
				    rxd->rx_dmamap);
				rxd->rx_dmamap = NULL;
			}
		}
		if (sc->vge_cdata.vge_rx_sparemap != NULL) {
			bus_dmamap_destroy(sc->vge_cdata.vge_rx_tag,
			    sc->vge_cdata.vge_rx_sparemap);
			sc->vge_cdata.vge_rx_sparemap = NULL;
		}
		bus_dma_tag_destroy(sc->vge_cdata.vge_rx_tag);
		sc->vge_cdata.vge_rx_tag = NULL;
	}

	if (sc->vge_cdata.vge_buffer_tag != NULL) {
		bus_dma_tag_destroy(sc->vge_cdata.vge_buffer_tag);
		sc->vge_cdata.vge_buffer_tag = NULL;
	}
	if (sc->vge_cdata.vge_ring_tag != NULL) {
		bus_dma_tag_destroy(sc->vge_cdata.vge_ring_tag);
		sc->vge_cdata.vge_ring_tag = NULL;
	}
}