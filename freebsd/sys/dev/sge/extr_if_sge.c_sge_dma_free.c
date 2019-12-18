#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sge_txdesc {int /*<<< orphan*/ * tx_dmamap; } ;
struct sge_list_data {scalar_t__ sge_rx_paddr; scalar_t__ sge_tx_paddr; int /*<<< orphan*/ * sge_tx_ring; int /*<<< orphan*/ * sge_rx_ring; } ;
struct sge_chain_data {int /*<<< orphan*/ * sge_tag; int /*<<< orphan*/ * sge_txmbuf_tag; struct sge_txdesc* sge_txdesc; int /*<<< orphan*/ * sge_rxmbuf_tag; int /*<<< orphan*/ * sge_rx_spare_map; struct sge_rxdesc* sge_rxdesc; int /*<<< orphan*/ * sge_tx_tag; int /*<<< orphan*/  sge_tx_dmamap; int /*<<< orphan*/ * sge_rx_tag; int /*<<< orphan*/  sge_rx_dmamap; } ;
struct sge_softc {struct sge_list_data sge_ldata; struct sge_chain_data sge_cdata; } ;
struct sge_rxdesc {int /*<<< orphan*/ * rx_dmamap; } ;

/* Variables and functions */
 int SGE_RX_RING_CNT ; 
 int SGE_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sge_dma_free(struct sge_softc *sc)
{
	struct sge_chain_data *cd;
	struct sge_list_data *ld;
	struct sge_rxdesc *rxd;
	struct sge_txdesc *txd;
	int i;

	cd = &sc->sge_cdata;
	ld = &sc->sge_ldata;
	/* Rx ring. */
	if (cd->sge_rx_tag != NULL) {
		if (ld->sge_rx_paddr != 0)
			bus_dmamap_unload(cd->sge_rx_tag, cd->sge_rx_dmamap);
		if (ld->sge_rx_ring != NULL)
			bus_dmamem_free(cd->sge_rx_tag, ld->sge_rx_ring,
			    cd->sge_rx_dmamap);
		ld->sge_rx_ring = NULL;
		ld->sge_rx_paddr = 0;
		bus_dma_tag_destroy(cd->sge_rx_tag);
		cd->sge_rx_tag = NULL;
	}
	/* Tx ring. */
	if (cd->sge_tx_tag != NULL) {
		if (ld->sge_tx_paddr != 0)
			bus_dmamap_unload(cd->sge_tx_tag, cd->sge_tx_dmamap);
		if (ld->sge_tx_ring != NULL)
			bus_dmamem_free(cd->sge_tx_tag, ld->sge_tx_ring,
			    cd->sge_tx_dmamap);
		ld->sge_tx_ring = NULL;
		ld->sge_tx_paddr = 0;
		bus_dma_tag_destroy(cd->sge_tx_tag);
		cd->sge_tx_tag = NULL;
	}
	/* Rx buffers. */
	if (cd->sge_rxmbuf_tag != NULL) {
		for (i = 0; i < SGE_RX_RING_CNT; i++) {
			rxd = &cd->sge_rxdesc[i];
			if (rxd->rx_dmamap != NULL) {
				bus_dmamap_destroy(cd->sge_rxmbuf_tag,
				    rxd->rx_dmamap);
				rxd->rx_dmamap = NULL;
			}
		}
		if (cd->sge_rx_spare_map != NULL) {
			bus_dmamap_destroy(cd->sge_rxmbuf_tag,
			    cd->sge_rx_spare_map);
			cd->sge_rx_spare_map = NULL;
		}
		bus_dma_tag_destroy(cd->sge_rxmbuf_tag);
		cd->sge_rxmbuf_tag = NULL;
	}
	/* Tx buffers. */
	if (cd->sge_txmbuf_tag != NULL) {
		for (i = 0; i < SGE_TX_RING_CNT; i++) {
			txd = &cd->sge_txdesc[i];
			if (txd->tx_dmamap != NULL) {
				bus_dmamap_destroy(cd->sge_txmbuf_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = NULL;
			}
		}
		bus_dma_tag_destroy(cd->sge_txmbuf_tag);
		cd->sge_txmbuf_tag = NULL;
	}
	if (cd->sge_tag != NULL)
		bus_dma_tag_destroy(cd->sge_tag);
	cd->sge_tag = NULL;
}