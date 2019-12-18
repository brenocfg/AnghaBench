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
struct vte_txdesc {int /*<<< orphan*/ * tx_dmamap; } ;
struct TYPE_2__ {scalar_t__ vte_tx_ring_paddr; scalar_t__ vte_rx_ring_paddr; int /*<<< orphan*/ * vte_parent_tag; int /*<<< orphan*/ * vte_buffer_tag; int /*<<< orphan*/ * vte_rx_ring_tag; int /*<<< orphan*/ * vte_rx_ring; int /*<<< orphan*/  vte_rx_ring_map; int /*<<< orphan*/ * vte_tx_ring_tag; int /*<<< orphan*/ * vte_tx_ring; int /*<<< orphan*/  vte_tx_ring_map; int /*<<< orphan*/ * vte_rx_tag; int /*<<< orphan*/ * vte_rx_sparemap; struct vte_rxdesc* vte_rxdesc; int /*<<< orphan*/ * vte_tx_tag; struct vte_txdesc* vte_txdesc; } ;
struct vte_softc {TYPE_1__ vte_cdata; } ;
struct vte_rxdesc {int /*<<< orphan*/ * rx_dmamap; } ;

/* Variables and functions */
 int VTE_RX_RING_CNT ; 
 int VTE_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vte_dma_free(struct vte_softc *sc)
{
	struct vte_txdesc *txd;
	struct vte_rxdesc *rxd;
	int i;

	/* TX buffers. */
	if (sc->vte_cdata.vte_tx_tag != NULL) {
		for (i = 0; i < VTE_TX_RING_CNT; i++) {
			txd = &sc->vte_cdata.vte_txdesc[i];
			if (txd->tx_dmamap != NULL) {
				bus_dmamap_destroy(sc->vte_cdata.vte_tx_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = NULL;
			}
		}
		bus_dma_tag_destroy(sc->vte_cdata.vte_tx_tag);
		sc->vte_cdata.vte_tx_tag = NULL;
	}
	/* RX buffers */
	if (sc->vte_cdata.vte_rx_tag != NULL) {
		for (i = 0; i < VTE_RX_RING_CNT; i++) {
			rxd = &sc->vte_cdata.vte_rxdesc[i];
			if (rxd->rx_dmamap != NULL) {
				bus_dmamap_destroy(sc->vte_cdata.vte_rx_tag,
				    rxd->rx_dmamap);
				rxd->rx_dmamap = NULL;
			}
		}
		if (sc->vte_cdata.vte_rx_sparemap != NULL) {
			bus_dmamap_destroy(sc->vte_cdata.vte_rx_tag,
			    sc->vte_cdata.vte_rx_sparemap);
			sc->vte_cdata.vte_rx_sparemap = NULL;
		}
		bus_dma_tag_destroy(sc->vte_cdata.vte_rx_tag);
		sc->vte_cdata.vte_rx_tag = NULL;
	}
	/* TX descriptor ring. */
	if (sc->vte_cdata.vte_tx_ring_tag != NULL) {
		if (sc->vte_cdata.vte_tx_ring_paddr != 0)
			bus_dmamap_unload(sc->vte_cdata.vte_tx_ring_tag,
			    sc->vte_cdata.vte_tx_ring_map);
		if (sc->vte_cdata.vte_tx_ring != NULL)
			bus_dmamem_free(sc->vte_cdata.vte_tx_ring_tag,
			    sc->vte_cdata.vte_tx_ring,
			    sc->vte_cdata.vte_tx_ring_map);
		sc->vte_cdata.vte_tx_ring = NULL;
		sc->vte_cdata.vte_tx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->vte_cdata.vte_tx_ring_tag);
		sc->vte_cdata.vte_tx_ring_tag = NULL;
	}
	/* RX ring. */
	if (sc->vte_cdata.vte_rx_ring_tag != NULL) {
		if (sc->vte_cdata.vte_rx_ring_paddr != 0)
			bus_dmamap_unload(sc->vte_cdata.vte_rx_ring_tag,
			    sc->vte_cdata.vte_rx_ring_map);
		if (sc->vte_cdata.vte_rx_ring != NULL)
			bus_dmamem_free(sc->vte_cdata.vte_rx_ring_tag,
			    sc->vte_cdata.vte_rx_ring,
			    sc->vte_cdata.vte_rx_ring_map);
		sc->vte_cdata.vte_rx_ring = NULL;
		sc->vte_cdata.vte_rx_ring_paddr = 0;
		bus_dma_tag_destroy(sc->vte_cdata.vte_rx_ring_tag);
		sc->vte_cdata.vte_rx_ring_tag = NULL;
	}
	if (sc->vte_cdata.vte_buffer_tag != NULL) {
		bus_dma_tag_destroy(sc->vte_cdata.vte_buffer_tag);
		sc->vte_cdata.vte_buffer_tag = NULL;
	}
	if (sc->vte_cdata.vte_parent_tag != NULL) {
		bus_dma_tag_destroy(sc->vte_cdata.vte_parent_tag);
		sc->vte_cdata.vte_parent_tag = NULL;
	}
}