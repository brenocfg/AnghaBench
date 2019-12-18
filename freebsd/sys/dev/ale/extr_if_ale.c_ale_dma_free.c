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
struct ale_txdesc {int /*<<< orphan*/ * tx_dmamap; } ;
struct TYPE_3__ {scalar_t__ ale_tx_ring_paddr; scalar_t__ ale_tx_cmb_paddr; int /*<<< orphan*/ * ale_parent_tag; int /*<<< orphan*/ * ale_buffer_tag; int /*<<< orphan*/ * ale_tx_cmb_tag; int /*<<< orphan*/ * ale_tx_cmb; int /*<<< orphan*/  ale_tx_cmb_map; TYPE_2__* ale_rx_page; int /*<<< orphan*/ * ale_tx_ring_tag; int /*<<< orphan*/ * ale_tx_ring; int /*<<< orphan*/  ale_tx_ring_map; int /*<<< orphan*/ * ale_tx_tag; struct ale_txdesc* ale_txdesc; } ;
struct ale_softc {TYPE_1__ ale_cdata; } ;
struct TYPE_4__ {scalar_t__ page_paddr; scalar_t__ cmb_paddr; int /*<<< orphan*/ * cmb_tag; int /*<<< orphan*/ * cmb_addr; int /*<<< orphan*/  cmb_map; int /*<<< orphan*/ * page_tag; int /*<<< orphan*/ * page_addr; int /*<<< orphan*/  page_map; } ;

/* Variables and functions */
 int ALE_RX_PAGES ; 
 int ALE_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ale_dma_free(struct ale_softc *sc)
{
	struct ale_txdesc *txd;
	int i;

	/* Tx buffers. */
	if (sc->ale_cdata.ale_tx_tag != NULL) {
		for (i = 0; i < ALE_TX_RING_CNT; i++) {
			txd = &sc->ale_cdata.ale_txdesc[i];
			if (txd->tx_dmamap != NULL) {
				bus_dmamap_destroy(sc->ale_cdata.ale_tx_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = NULL;
			}
		}
		bus_dma_tag_destroy(sc->ale_cdata.ale_tx_tag);
		sc->ale_cdata.ale_tx_tag = NULL;
	}
	/* Tx descriptor ring. */
	if (sc->ale_cdata.ale_tx_ring_tag != NULL) {
		if (sc->ale_cdata.ale_tx_ring_paddr != 0)
			bus_dmamap_unload(sc->ale_cdata.ale_tx_ring_tag,
			    sc->ale_cdata.ale_tx_ring_map);
		if (sc->ale_cdata.ale_tx_ring != NULL)
			bus_dmamem_free(sc->ale_cdata.ale_tx_ring_tag,
			    sc->ale_cdata.ale_tx_ring,
			    sc->ale_cdata.ale_tx_ring_map);
		sc->ale_cdata.ale_tx_ring_paddr = 0;
		sc->ale_cdata.ale_tx_ring = NULL;
		bus_dma_tag_destroy(sc->ale_cdata.ale_tx_ring_tag);
		sc->ale_cdata.ale_tx_ring_tag = NULL;
	}
	/* Rx page block. */
	for (i = 0; i < ALE_RX_PAGES; i++) {
		if (sc->ale_cdata.ale_rx_page[i].page_tag != NULL) {
			if (sc->ale_cdata.ale_rx_page[i].page_paddr != 0)
				bus_dmamap_unload(
				    sc->ale_cdata.ale_rx_page[i].page_tag,
				    sc->ale_cdata.ale_rx_page[i].page_map);
			if (sc->ale_cdata.ale_rx_page[i].page_addr != NULL)
				bus_dmamem_free(
				    sc->ale_cdata.ale_rx_page[i].page_tag,
				    sc->ale_cdata.ale_rx_page[i].page_addr,
				    sc->ale_cdata.ale_rx_page[i].page_map);
			sc->ale_cdata.ale_rx_page[i].page_paddr = 0;
			sc->ale_cdata.ale_rx_page[i].page_addr = NULL;
			bus_dma_tag_destroy(
			    sc->ale_cdata.ale_rx_page[i].page_tag);
			sc->ale_cdata.ale_rx_page[i].page_tag = NULL;
		}
	}
	/* Rx CMB. */
	for (i = 0; i < ALE_RX_PAGES; i++) {
		if (sc->ale_cdata.ale_rx_page[i].cmb_tag != NULL) {
			if (sc->ale_cdata.ale_rx_page[i].cmb_paddr != 0)
				bus_dmamap_unload(
				    sc->ale_cdata.ale_rx_page[i].cmb_tag,
				    sc->ale_cdata.ale_rx_page[i].cmb_map);
			if (sc->ale_cdata.ale_rx_page[i].cmb_addr != NULL)
				bus_dmamem_free(
				    sc->ale_cdata.ale_rx_page[i].cmb_tag,
				    sc->ale_cdata.ale_rx_page[i].cmb_addr,
				    sc->ale_cdata.ale_rx_page[i].cmb_map);
			sc->ale_cdata.ale_rx_page[i].cmb_paddr = 0;
			sc->ale_cdata.ale_rx_page[i].cmb_addr = NULL;
			bus_dma_tag_destroy(
			    sc->ale_cdata.ale_rx_page[i].cmb_tag);
			sc->ale_cdata.ale_rx_page[i].cmb_tag = NULL;
		}
	}
	/* Tx CMB. */
	if (sc->ale_cdata.ale_tx_cmb_tag != NULL) {
		if (sc->ale_cdata.ale_tx_cmb_paddr != 0)
			bus_dmamap_unload(sc->ale_cdata.ale_tx_cmb_tag,
			    sc->ale_cdata.ale_tx_cmb_map);
		if (sc->ale_cdata.ale_tx_cmb != NULL)
			bus_dmamem_free(sc->ale_cdata.ale_tx_cmb_tag,
			    sc->ale_cdata.ale_tx_cmb,
			    sc->ale_cdata.ale_tx_cmb_map);
		sc->ale_cdata.ale_tx_cmb_paddr = 0;
		sc->ale_cdata.ale_tx_cmb = NULL;
		bus_dma_tag_destroy(sc->ale_cdata.ale_tx_cmb_tag);
		sc->ale_cdata.ale_tx_cmb_tag = NULL;
	}
	if (sc->ale_cdata.ale_buffer_tag != NULL) {
		bus_dma_tag_destroy(sc->ale_cdata.ale_buffer_tag);
		sc->ale_cdata.ale_buffer_tag = NULL;
	}
	if (sc->ale_cdata.ale_parent_tag != NULL) {
		bus_dma_tag_destroy(sc->ale_cdata.ale_parent_tag);
		sc->ale_cdata.ale_parent_tag = NULL;
	}
}