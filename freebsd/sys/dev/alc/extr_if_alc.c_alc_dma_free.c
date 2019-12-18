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
struct alc_txdesc {int /*<<< orphan*/ * tx_dmamap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * alc_parent_tag; int /*<<< orphan*/ * alc_buffer_tag; int /*<<< orphan*/ * alc_smb_tag; int /*<<< orphan*/  alc_smb_map; int /*<<< orphan*/ * alc_cmb_tag; int /*<<< orphan*/  alc_cmb_map; int /*<<< orphan*/ * alc_rr_ring_tag; int /*<<< orphan*/  alc_rr_ring_map; int /*<<< orphan*/ * alc_rx_ring_tag; int /*<<< orphan*/  alc_rx_ring_map; int /*<<< orphan*/ * alc_tx_ring_tag; int /*<<< orphan*/  alc_tx_ring_map; int /*<<< orphan*/ * alc_rx_tag; int /*<<< orphan*/ * alc_rx_sparemap; struct alc_rxdesc* alc_rxdesc; int /*<<< orphan*/ * alc_tx_tag; struct alc_txdesc* alc_txdesc; } ;
struct TYPE_3__ {scalar_t__ alc_tx_ring_paddr; scalar_t__ alc_rx_ring_paddr; scalar_t__ alc_rr_ring_paddr; scalar_t__ alc_cmb_paddr; scalar_t__ alc_smb_paddr; int /*<<< orphan*/ * alc_smb; int /*<<< orphan*/ * alc_cmb; int /*<<< orphan*/ * alc_rr_ring; int /*<<< orphan*/ * alc_rx_ring; int /*<<< orphan*/ * alc_tx_ring; } ;
struct alc_softc {TYPE_2__ alc_cdata; TYPE_1__ alc_rdata; } ;
struct alc_rxdesc {int /*<<< orphan*/ * rx_dmamap; } ;

/* Variables and functions */
 int ALC_RX_RING_CNT ; 
 int ALC_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alc_dma_free(struct alc_softc *sc)
{
	struct alc_txdesc *txd;
	struct alc_rxdesc *rxd;
	int i;

	/* Tx buffers. */
	if (sc->alc_cdata.alc_tx_tag != NULL) {
		for (i = 0; i < ALC_TX_RING_CNT; i++) {
			txd = &sc->alc_cdata.alc_txdesc[i];
			if (txd->tx_dmamap != NULL) {
				bus_dmamap_destroy(sc->alc_cdata.alc_tx_tag,
				    txd->tx_dmamap);
				txd->tx_dmamap = NULL;
			}
		}
		bus_dma_tag_destroy(sc->alc_cdata.alc_tx_tag);
		sc->alc_cdata.alc_tx_tag = NULL;
	}
	/* Rx buffers */
	if (sc->alc_cdata.alc_rx_tag != NULL) {
		for (i = 0; i < ALC_RX_RING_CNT; i++) {
			rxd = &sc->alc_cdata.alc_rxdesc[i];
			if (rxd->rx_dmamap != NULL) {
				bus_dmamap_destroy(sc->alc_cdata.alc_rx_tag,
				    rxd->rx_dmamap);
				rxd->rx_dmamap = NULL;
			}
		}
		if (sc->alc_cdata.alc_rx_sparemap != NULL) {
			bus_dmamap_destroy(sc->alc_cdata.alc_rx_tag,
			    sc->alc_cdata.alc_rx_sparemap);
			sc->alc_cdata.alc_rx_sparemap = NULL;
		}
		bus_dma_tag_destroy(sc->alc_cdata.alc_rx_tag);
		sc->alc_cdata.alc_rx_tag = NULL;
	}
	/* Tx descriptor ring. */
	if (sc->alc_cdata.alc_tx_ring_tag != NULL) {
		if (sc->alc_rdata.alc_tx_ring_paddr != 0)
			bus_dmamap_unload(sc->alc_cdata.alc_tx_ring_tag,
			    sc->alc_cdata.alc_tx_ring_map);
		if (sc->alc_rdata.alc_tx_ring != NULL)
			bus_dmamem_free(sc->alc_cdata.alc_tx_ring_tag,
			    sc->alc_rdata.alc_tx_ring,
			    sc->alc_cdata.alc_tx_ring_map);
		sc->alc_rdata.alc_tx_ring_paddr = 0;
		sc->alc_rdata.alc_tx_ring = NULL;
		bus_dma_tag_destroy(sc->alc_cdata.alc_tx_ring_tag);
		sc->alc_cdata.alc_tx_ring_tag = NULL;
	}
	/* Rx ring. */
	if (sc->alc_cdata.alc_rx_ring_tag != NULL) {
		if (sc->alc_rdata.alc_rx_ring_paddr != 0)
			bus_dmamap_unload(sc->alc_cdata.alc_rx_ring_tag,
			    sc->alc_cdata.alc_rx_ring_map);
		if (sc->alc_rdata.alc_rx_ring != NULL)
			bus_dmamem_free(sc->alc_cdata.alc_rx_ring_tag,
			    sc->alc_rdata.alc_rx_ring,
			    sc->alc_cdata.alc_rx_ring_map);
		sc->alc_rdata.alc_rx_ring_paddr = 0;
		sc->alc_rdata.alc_rx_ring = NULL;
		bus_dma_tag_destroy(sc->alc_cdata.alc_rx_ring_tag);
		sc->alc_cdata.alc_rx_ring_tag = NULL;
	}
	/* Rx return ring. */
	if (sc->alc_cdata.alc_rr_ring_tag != NULL) {
		if (sc->alc_rdata.alc_rr_ring_paddr != 0)
			bus_dmamap_unload(sc->alc_cdata.alc_rr_ring_tag,
			    sc->alc_cdata.alc_rr_ring_map);
		if (sc->alc_rdata.alc_rr_ring != NULL)
			bus_dmamem_free(sc->alc_cdata.alc_rr_ring_tag,
			    sc->alc_rdata.alc_rr_ring,
			    sc->alc_cdata.alc_rr_ring_map);
		sc->alc_rdata.alc_rr_ring_paddr = 0;
		sc->alc_rdata.alc_rr_ring = NULL;
		bus_dma_tag_destroy(sc->alc_cdata.alc_rr_ring_tag);
		sc->alc_cdata.alc_rr_ring_tag = NULL;
	}
	/* CMB block */
	if (sc->alc_cdata.alc_cmb_tag != NULL) {
		if (sc->alc_rdata.alc_cmb_paddr != 0)
			bus_dmamap_unload(sc->alc_cdata.alc_cmb_tag,
			    sc->alc_cdata.alc_cmb_map);
		if (sc->alc_rdata.alc_cmb != NULL)
			bus_dmamem_free(sc->alc_cdata.alc_cmb_tag,
			    sc->alc_rdata.alc_cmb,
			    sc->alc_cdata.alc_cmb_map);		
		sc->alc_rdata.alc_cmb_paddr = 0;
		sc->alc_rdata.alc_cmb = NULL;
		bus_dma_tag_destroy(sc->alc_cdata.alc_cmb_tag);
		sc->alc_cdata.alc_cmb_tag = NULL;
	}
	/* SMB block */
	if (sc->alc_cdata.alc_smb_tag != NULL) {
		if (sc->alc_rdata.alc_smb_paddr != 0)
			bus_dmamap_unload(sc->alc_cdata.alc_smb_tag,
			    sc->alc_cdata.alc_smb_map);
		if (sc->alc_rdata.alc_smb != NULL)
			bus_dmamem_free(sc->alc_cdata.alc_smb_tag,
			    sc->alc_rdata.alc_smb,
			    sc->alc_cdata.alc_smb_map);
		sc->alc_rdata.alc_smb_paddr = 0;
		sc->alc_rdata.alc_smb = NULL;
		bus_dma_tag_destroy(sc->alc_cdata.alc_smb_tag);
		sc->alc_cdata.alc_smb_tag = NULL;
	}
	if (sc->alc_cdata.alc_buffer_tag != NULL) {
		bus_dma_tag_destroy(sc->alc_cdata.alc_buffer_tag);
		sc->alc_cdata.alc_buffer_tag = NULL;
	}
	if (sc->alc_cdata.alc_parent_tag != NULL) {
		bus_dma_tag_destroy(sc->alc_cdata.alc_parent_tag);
		sc->alc_cdata.alc_parent_tag = NULL;
	}
}