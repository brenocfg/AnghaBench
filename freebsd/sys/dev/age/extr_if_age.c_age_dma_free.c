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
struct age_txdesc {int /*<<< orphan*/ * tx_dmamap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * age_parent_tag; int /*<<< orphan*/ * age_buffer_tag; int /*<<< orphan*/ * age_smb_block_tag; int /*<<< orphan*/  age_smb_block_map; int /*<<< orphan*/ * age_cmb_block_tag; int /*<<< orphan*/  age_cmb_block_map; int /*<<< orphan*/ * age_rr_ring_tag; int /*<<< orphan*/  age_rr_ring_map; int /*<<< orphan*/ * age_rx_ring_tag; int /*<<< orphan*/  age_rx_ring_map; int /*<<< orphan*/ * age_tx_ring_tag; int /*<<< orphan*/  age_tx_ring_map; int /*<<< orphan*/ * age_rx_tag; int /*<<< orphan*/ * age_rx_sparemap; struct age_rxdesc* age_rxdesc; int /*<<< orphan*/ * age_tx_tag; struct age_txdesc* age_txdesc; } ;
struct TYPE_3__ {scalar_t__ age_tx_ring_paddr; scalar_t__ age_rx_ring_paddr; scalar_t__ age_rr_ring_paddr; scalar_t__ age_cmb_block_paddr; scalar_t__ age_smb_block_paddr; int /*<<< orphan*/ * age_smb_block; int /*<<< orphan*/ * age_cmb_block; int /*<<< orphan*/ * age_rr_ring; int /*<<< orphan*/ * age_rx_ring; int /*<<< orphan*/ * age_tx_ring; } ;
struct age_softc {TYPE_2__ age_cdata; TYPE_1__ age_rdata; } ;
struct age_rxdesc {int /*<<< orphan*/ * rx_dmamap; } ;

/* Variables and functions */
 int AGE_RX_RING_CNT ; 
 int AGE_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
age_dma_free(struct age_softc *sc)
{
	struct age_txdesc *txd;
	struct age_rxdesc *rxd;
	int i;

	/* Tx buffers */
	if (sc->age_cdata.age_tx_tag != NULL) {
		for (i = 0; i < AGE_TX_RING_CNT; i++) {
			txd = &sc->age_cdata.age_txdesc[i];
			if (txd->tx_dmamap != NULL) {
				bus_dmamap_destroy(sc->age_cdata.age_tx_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = NULL;
			}
		}
		bus_dma_tag_destroy(sc->age_cdata.age_tx_tag);
		sc->age_cdata.age_tx_tag = NULL;
	}
	/* Rx buffers */
	if (sc->age_cdata.age_rx_tag != NULL) {
		for (i = 0; i < AGE_RX_RING_CNT; i++) {
			rxd = &sc->age_cdata.age_rxdesc[i];
			if (rxd->rx_dmamap != NULL) {
				bus_dmamap_destroy(sc->age_cdata.age_rx_tag,
				    rxd->rx_dmamap);
				rxd->rx_dmamap = NULL;
			}
		}
		if (sc->age_cdata.age_rx_sparemap != NULL) {
			bus_dmamap_destroy(sc->age_cdata.age_rx_tag,
			    sc->age_cdata.age_rx_sparemap);
			sc->age_cdata.age_rx_sparemap = NULL;
		}
		bus_dma_tag_destroy(sc->age_cdata.age_rx_tag);
		sc->age_cdata.age_rx_tag = NULL;
	}
	/* Tx ring. */
	if (sc->age_cdata.age_tx_ring_tag != NULL) {
		if (sc->age_rdata.age_tx_ring_paddr != 0)
			bus_dmamap_unload(sc->age_cdata.age_tx_ring_tag,
			    sc->age_cdata.age_tx_ring_map);
		if (sc->age_rdata.age_tx_ring != NULL)
			bus_dmamem_free(sc->age_cdata.age_tx_ring_tag,
			    sc->age_rdata.age_tx_ring,
			    sc->age_cdata.age_tx_ring_map);
		sc->age_rdata.age_tx_ring_paddr = 0;
		sc->age_rdata.age_tx_ring = NULL;
		bus_dma_tag_destroy(sc->age_cdata.age_tx_ring_tag);
		sc->age_cdata.age_tx_ring_tag = NULL;
	}
	/* Rx ring. */
	if (sc->age_cdata.age_rx_ring_tag != NULL) {
		if (sc->age_rdata.age_rx_ring_paddr != 0)
			bus_dmamap_unload(sc->age_cdata.age_rx_ring_tag,
			    sc->age_cdata.age_rx_ring_map);
		if (sc->age_rdata.age_rx_ring != NULL)
			bus_dmamem_free(sc->age_cdata.age_rx_ring_tag,
			    sc->age_rdata.age_rx_ring,
			    sc->age_cdata.age_rx_ring_map);
		sc->age_rdata.age_rx_ring_paddr = 0;
		sc->age_rdata.age_rx_ring = NULL;
		bus_dma_tag_destroy(sc->age_cdata.age_rx_ring_tag);
		sc->age_cdata.age_rx_ring_tag = NULL;
	}
	/* Rx return ring. */
	if (sc->age_cdata.age_rr_ring_tag != NULL) {
		if (sc->age_rdata.age_rr_ring_paddr != 0)
			bus_dmamap_unload(sc->age_cdata.age_rr_ring_tag,
			    sc->age_cdata.age_rr_ring_map);
		if (sc->age_rdata.age_rr_ring != NULL)
			bus_dmamem_free(sc->age_cdata.age_rr_ring_tag,
			    sc->age_rdata.age_rr_ring,
			    sc->age_cdata.age_rr_ring_map);
		sc->age_rdata.age_rr_ring_paddr = 0;
		sc->age_rdata.age_rr_ring = NULL;
		bus_dma_tag_destroy(sc->age_cdata.age_rr_ring_tag);
		sc->age_cdata.age_rr_ring_tag = NULL;
	}
	/* CMB block */
	if (sc->age_cdata.age_cmb_block_tag != NULL) {
		if (sc->age_rdata.age_cmb_block_paddr != 0)
			bus_dmamap_unload(sc->age_cdata.age_cmb_block_tag,
			    sc->age_cdata.age_cmb_block_map);
		if (sc->age_rdata.age_cmb_block != NULL)
			bus_dmamem_free(sc->age_cdata.age_cmb_block_tag,
			    sc->age_rdata.age_cmb_block,
			    sc->age_cdata.age_cmb_block_map);
		sc->age_rdata.age_cmb_block_paddr = 0;
		sc->age_rdata.age_cmb_block = NULL;
		bus_dma_tag_destroy(sc->age_cdata.age_cmb_block_tag);
		sc->age_cdata.age_cmb_block_tag = NULL;
	}
	/* SMB block */
	if (sc->age_cdata.age_smb_block_tag != NULL) {
		if (sc->age_rdata.age_smb_block_paddr != 0)
			bus_dmamap_unload(sc->age_cdata.age_smb_block_tag,
			    sc->age_cdata.age_smb_block_map);
		if (sc->age_rdata.age_smb_block != NULL)
			bus_dmamem_free(sc->age_cdata.age_smb_block_tag,
			    sc->age_rdata.age_smb_block,
			    sc->age_cdata.age_smb_block_map);
		sc->age_rdata.age_smb_block_paddr = 0;
		sc->age_rdata.age_smb_block = NULL;
		bus_dma_tag_destroy(sc->age_cdata.age_smb_block_tag);
		sc->age_cdata.age_smb_block_tag = NULL;
	}

	if (sc->age_cdata.age_buffer_tag != NULL) {
		bus_dma_tag_destroy(sc->age_cdata.age_buffer_tag);
		sc->age_cdata.age_buffer_tag = NULL;
	}
	if (sc->age_cdata.age_parent_tag != NULL) {
		bus_dma_tag_destroy(sc->age_cdata.age_parent_tag);
		sc->age_cdata.age_parent_tag = NULL;
	}
}