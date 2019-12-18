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
struct sis_txdesc {scalar_t__ tx_dmamap; } ;
struct sis_softc {scalar_t__ sis_parent_tag; scalar_t__ sis_tx_list_tag; int /*<<< orphan*/  sis_tx_list_map; scalar_t__ sis_tx_list; scalar_t__ sis_tx_paddr; scalar_t__ sis_rx_list_tag; int /*<<< orphan*/  sis_rx_list_map; scalar_t__ sis_rx_list; scalar_t__ sis_rx_paddr; scalar_t__ sis_tx_tag; scalar_t__ sis_rx_tag; struct sis_txdesc* sis_txdesc; scalar_t__ sis_rx_sparemap; struct sis_rxdesc* sis_rxdesc; } ;
struct sis_rxdesc {scalar_t__ rx_dmamap; } ;

/* Variables and functions */
 int SIS_RX_LIST_CNT ; 
 int SIS_TX_LIST_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sis_dma_free(struct sis_softc *sc)
{
	struct sis_rxdesc	*rxd;
	struct sis_txdesc	*txd;
	int			i;

	/* Destroy DMA maps for RX buffers. */
	for (i = 0; i < SIS_RX_LIST_CNT; i++) {
		rxd = &sc->sis_rxdesc[i];
		if (rxd->rx_dmamap)
			bus_dmamap_destroy(sc->sis_rx_tag, rxd->rx_dmamap);
	}
	if (sc->sis_rx_sparemap)
		bus_dmamap_destroy(sc->sis_rx_tag, sc->sis_rx_sparemap);

	/* Destroy DMA maps for TX buffers. */
	for (i = 0; i < SIS_TX_LIST_CNT; i++) {
		txd = &sc->sis_txdesc[i];
		if (txd->tx_dmamap)
			bus_dmamap_destroy(sc->sis_tx_tag, txd->tx_dmamap);
	}

	if (sc->sis_rx_tag)
		bus_dma_tag_destroy(sc->sis_rx_tag);
	if (sc->sis_tx_tag)
		bus_dma_tag_destroy(sc->sis_tx_tag);

	/* Destroy RX ring. */
	if (sc->sis_rx_paddr)
		bus_dmamap_unload(sc->sis_rx_list_tag, sc->sis_rx_list_map);
	if (sc->sis_rx_list)
		bus_dmamem_free(sc->sis_rx_list_tag, sc->sis_rx_list,
		    sc->sis_rx_list_map);

	if (sc->sis_rx_list_tag)
		bus_dma_tag_destroy(sc->sis_rx_list_tag);

	/* Destroy TX ring. */
	if (sc->sis_tx_paddr)
		bus_dmamap_unload(sc->sis_tx_list_tag, sc->sis_tx_list_map);

	if (sc->sis_tx_list)
		bus_dmamem_free(sc->sis_tx_list_tag, sc->sis_tx_list,
		    sc->sis_tx_list_map);

	if (sc->sis_tx_list_tag)
		bus_dma_tag_destroy(sc->sis_tx_list_tag);

	/* Destroy the parent tag. */
	if (sc->sis_parent_tag)
		bus_dma_tag_destroy(sc->sis_parent_tag);
}