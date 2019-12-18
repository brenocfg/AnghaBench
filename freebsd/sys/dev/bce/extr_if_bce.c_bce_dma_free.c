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
struct bce_softc {scalar_t__ status_block_paddr; scalar_t__ stats_block_paddr; int ctx_pages; scalar_t__* ctx_paddr; int tx_pages; scalar_t__* tx_bd_chain_paddr; int rx_pages; scalar_t__* rx_bd_chain_paddr; int pg_pages; scalar_t__* pg_bd_chain_paddr; int /*<<< orphan*/ * parent_tag; int /*<<< orphan*/ * pg_mbuf_tag; int /*<<< orphan*/ ** pg_mbuf_map; int /*<<< orphan*/ * rx_mbuf_tag; int /*<<< orphan*/ ** rx_mbuf_map; int /*<<< orphan*/ * tx_mbuf_tag; int /*<<< orphan*/ ** tx_mbuf_map; int /*<<< orphan*/ * pg_bd_chain_tag; int /*<<< orphan*/ ** pg_bd_chain; int /*<<< orphan*/ ** pg_bd_chain_map; int /*<<< orphan*/ * rx_bd_chain_tag; int /*<<< orphan*/ ** rx_bd_chain; int /*<<< orphan*/ ** rx_bd_chain_map; int /*<<< orphan*/ * tx_bd_chain_tag; int /*<<< orphan*/ ** tx_bd_chain; int /*<<< orphan*/ ** tx_bd_chain_map; int /*<<< orphan*/ * ctx_tag; int /*<<< orphan*/ ** ctx_block; int /*<<< orphan*/ ** ctx_map; int /*<<< orphan*/ * stats_tag; int /*<<< orphan*/ * stats_block; int /*<<< orphan*/ * stats_map; int /*<<< orphan*/ * status_tag; int /*<<< orphan*/ * status_block; int /*<<< orphan*/ * status_map; } ;

/* Variables and functions */
 scalar_t__ BCE_CHIP_NUM (struct bce_softc*) ; 
 scalar_t__ BCE_CHIP_NUM_5709 ; 
 int BCE_VERBOSE_CTX ; 
 int BCE_VERBOSE_RESET ; 
 int BCE_VERBOSE_UNLOAD ; 
 int /*<<< orphan*/  DBENTER (int) ; 
 int /*<<< orphan*/  DBEXIT (int) ; 
 int MAX_PG_BD_AVAIL ; 
 int MAX_RX_BD_AVAIL ; 
 int MAX_TX_BD_AVAIL ; 
 scalar_t__ TRUE ; 
 scalar_t__ bce_hdr_split ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bce_dma_free(struct bce_softc *sc)
{
	int i;

	DBENTER(BCE_VERBOSE_RESET | BCE_VERBOSE_UNLOAD | BCE_VERBOSE_CTX);

	/* Free, unmap, and destroy the status block. */
	if (sc->status_block_paddr != 0) {
		bus_dmamap_unload(
		    sc->status_tag,
		    sc->status_map);
		sc->status_block_paddr = 0;
	}

	if (sc->status_block != NULL) {
		bus_dmamem_free(
		   sc->status_tag,
		    sc->status_block,
		    sc->status_map);
		sc->status_block = NULL;
	}

	if (sc->status_tag != NULL) {
		bus_dma_tag_destroy(sc->status_tag);
		sc->status_tag = NULL;
	}


	/* Free, unmap, and destroy the statistics block. */
	if (sc->stats_block_paddr != 0) {
		bus_dmamap_unload(
		    sc->stats_tag,
		    sc->stats_map);
		sc->stats_block_paddr = 0;
	}

	if (sc->stats_block != NULL) {
		bus_dmamem_free(
		    sc->stats_tag,
		    sc->stats_block,
		    sc->stats_map);
		sc->stats_block = NULL;
	}

	if (sc->stats_tag != NULL) {
		bus_dma_tag_destroy(sc->stats_tag);
		sc->stats_tag = NULL;
	}


	/* Free, unmap and destroy all context memory pages. */
	if (BCE_CHIP_NUM(sc) == BCE_CHIP_NUM_5709) {
		for (i = 0; i < sc->ctx_pages; i++ ) {
			if (sc->ctx_paddr[i] != 0) {
				bus_dmamap_unload(
				    sc->ctx_tag,
				    sc->ctx_map[i]);
				sc->ctx_paddr[i] = 0;
			}

			if (sc->ctx_block[i] != NULL) {
				bus_dmamem_free(
				    sc->ctx_tag,
				    sc->ctx_block[i],
				    sc->ctx_map[i]);
				sc->ctx_block[i] = NULL;
			}
		}

		/* Destroy the context memory tag. */
		if (sc->ctx_tag != NULL) {
			bus_dma_tag_destroy(sc->ctx_tag);
			sc->ctx_tag = NULL;
		}
	}


	/* Free, unmap and destroy all TX buffer descriptor chain pages. */
	for (i = 0; i < sc->tx_pages; i++ ) {
		if (sc->tx_bd_chain_paddr[i] != 0) {
			bus_dmamap_unload(
			    sc->tx_bd_chain_tag,
			    sc->tx_bd_chain_map[i]);
			sc->tx_bd_chain_paddr[i] = 0;
		}

		if (sc->tx_bd_chain[i] != NULL) {
			bus_dmamem_free(
			    sc->tx_bd_chain_tag,
			    sc->tx_bd_chain[i],
			    sc->tx_bd_chain_map[i]);
			sc->tx_bd_chain[i] = NULL;
		}
	}

	/* Destroy the TX buffer descriptor tag. */
	if (sc->tx_bd_chain_tag != NULL) {
		bus_dma_tag_destroy(sc->tx_bd_chain_tag);
		sc->tx_bd_chain_tag = NULL;
	}


	/* Free, unmap and destroy all RX buffer descriptor chain pages. */
	for (i = 0; i < sc->rx_pages; i++ ) {
		if (sc->rx_bd_chain_paddr[i] != 0) {
			bus_dmamap_unload(
			    sc->rx_bd_chain_tag,
			    sc->rx_bd_chain_map[i]);
			sc->rx_bd_chain_paddr[i] = 0;
		}

		if (sc->rx_bd_chain[i] != NULL) {
			bus_dmamem_free(
			    sc->rx_bd_chain_tag,
			    sc->rx_bd_chain[i],
			    sc->rx_bd_chain_map[i]);
			sc->rx_bd_chain[i] = NULL;
		}
	}

	/* Destroy the RX buffer descriptor tag. */
	if (sc->rx_bd_chain_tag != NULL) {
		bus_dma_tag_destroy(sc->rx_bd_chain_tag);
		sc->rx_bd_chain_tag = NULL;
	}


	/* Free, unmap and destroy all page buffer descriptor chain pages. */
	if (bce_hdr_split == TRUE) {
		for (i = 0; i < sc->pg_pages; i++ ) {
			if (sc->pg_bd_chain_paddr[i] != 0) {
				bus_dmamap_unload(
				    sc->pg_bd_chain_tag,
				    sc->pg_bd_chain_map[i]);
				sc->pg_bd_chain_paddr[i] = 0;
			}

			if (sc->pg_bd_chain[i] != NULL) {
				bus_dmamem_free(
				    sc->pg_bd_chain_tag,
				    sc->pg_bd_chain[i],
				    sc->pg_bd_chain_map[i]);
				sc->pg_bd_chain[i] = NULL;
			}
		}

		/* Destroy the page buffer descriptor tag. */
		if (sc->pg_bd_chain_tag != NULL) {
			bus_dma_tag_destroy(sc->pg_bd_chain_tag);
			sc->pg_bd_chain_tag = NULL;
		}
	}


	/* Unload and destroy the TX mbuf maps. */
	for (i = 0; i < MAX_TX_BD_AVAIL; i++) {
		if (sc->tx_mbuf_map[i] != NULL) {
			bus_dmamap_unload(sc->tx_mbuf_tag,
			    sc->tx_mbuf_map[i]);
			bus_dmamap_destroy(sc->tx_mbuf_tag,
	 		    sc->tx_mbuf_map[i]);
			sc->tx_mbuf_map[i] = NULL;
		}
	}

	/* Destroy the TX mbuf tag. */
	if (sc->tx_mbuf_tag != NULL) {
		bus_dma_tag_destroy(sc->tx_mbuf_tag);
		sc->tx_mbuf_tag = NULL;
	}

	/* Unload and destroy the RX mbuf maps. */
	for (i = 0; i < MAX_RX_BD_AVAIL; i++) {
		if (sc->rx_mbuf_map[i] != NULL) {
			bus_dmamap_unload(sc->rx_mbuf_tag,
			    sc->rx_mbuf_map[i]);
			bus_dmamap_destroy(sc->rx_mbuf_tag,
	 		    sc->rx_mbuf_map[i]);
			sc->rx_mbuf_map[i] = NULL;
		}
	}

	/* Destroy the RX mbuf tag. */
	if (sc->rx_mbuf_tag != NULL) {
		bus_dma_tag_destroy(sc->rx_mbuf_tag);
		sc->rx_mbuf_tag = NULL;
	}

	/* Unload and destroy the page mbuf maps. */
	if (bce_hdr_split == TRUE) {
		for (i = 0; i < MAX_PG_BD_AVAIL; i++) {
			if (sc->pg_mbuf_map[i] != NULL) {
				bus_dmamap_unload(sc->pg_mbuf_tag,
				    sc->pg_mbuf_map[i]);
				bus_dmamap_destroy(sc->pg_mbuf_tag,
				    sc->pg_mbuf_map[i]);
				sc->pg_mbuf_map[i] = NULL;
			}
		}

		/* Destroy the page mbuf tag. */
		if (sc->pg_mbuf_tag != NULL) {
			bus_dma_tag_destroy(sc->pg_mbuf_tag);
			sc->pg_mbuf_tag = NULL;
		}
	}

	/* Destroy the parent tag */
	if (sc->parent_tag != NULL) {
		bus_dma_tag_destroy(sc->parent_tag);
		sc->parent_tag = NULL;
	}

	DBEXIT(BCE_VERBOSE_RESET | BCE_VERBOSE_UNLOAD | BCE_VERBOSE_CTX);
}