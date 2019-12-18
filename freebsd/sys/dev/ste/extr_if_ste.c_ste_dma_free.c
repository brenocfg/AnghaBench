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
struct TYPE_4__ {int /*<<< orphan*/ * ste_parent_tag; int /*<<< orphan*/ * ste_rx_list_tag; int /*<<< orphan*/  ste_rx_list_map; int /*<<< orphan*/ * ste_tx_list_tag; int /*<<< orphan*/  ste_tx_list_map; int /*<<< orphan*/ * ste_rx_tag; int /*<<< orphan*/ * ste_rx_sparemap; struct ste_chain_onefrag* ste_rx_chain; int /*<<< orphan*/ * ste_tx_tag; struct ste_chain* ste_tx_chain; } ;
struct TYPE_3__ {scalar_t__ ste_tx_list_paddr; scalar_t__ ste_rx_list_paddr; int /*<<< orphan*/ * ste_rx_list; int /*<<< orphan*/ * ste_tx_list; } ;
struct ste_softc {TYPE_2__ ste_cdata; TYPE_1__ ste_ldata; } ;
struct ste_chain_onefrag {int /*<<< orphan*/ * ste_map; } ;
struct ste_chain {int /*<<< orphan*/ * ste_map; } ;

/* Variables and functions */
 int STE_RX_LIST_CNT ; 
 int STE_TX_LIST_CNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ste_dma_free(struct ste_softc *sc)
{
	struct ste_chain *txc;
	struct ste_chain_onefrag *rxc;
	int i;

	/* Tx buffers. */
	if (sc->ste_cdata.ste_tx_tag != NULL) {
		for (i = 0; i < STE_TX_LIST_CNT; i++) {
			txc = &sc->ste_cdata.ste_tx_chain[i];
			if (txc->ste_map != NULL) {
				bus_dmamap_destroy(sc->ste_cdata.ste_tx_tag,
				    txc->ste_map);
				txc->ste_map = NULL;
			}
		}
		bus_dma_tag_destroy(sc->ste_cdata.ste_tx_tag);
		sc->ste_cdata.ste_tx_tag = NULL;
	}
	/* Rx buffers. */
	if (sc->ste_cdata.ste_rx_tag != NULL) {
		for (i = 0; i < STE_RX_LIST_CNT; i++) {
			rxc = &sc->ste_cdata.ste_rx_chain[i];
			if (rxc->ste_map != NULL) {
				bus_dmamap_destroy(sc->ste_cdata.ste_rx_tag,
				    rxc->ste_map);
				rxc->ste_map = NULL;
			}
		}
		if (sc->ste_cdata.ste_rx_sparemap != NULL) {
			bus_dmamap_destroy(sc->ste_cdata.ste_rx_tag,
			    sc->ste_cdata.ste_rx_sparemap);
			sc->ste_cdata.ste_rx_sparemap = NULL;
		}
		bus_dma_tag_destroy(sc->ste_cdata.ste_rx_tag);
		sc->ste_cdata.ste_rx_tag = NULL;
	}
	/* Tx descriptor list. */
	if (sc->ste_cdata.ste_tx_list_tag != NULL) {
		if (sc->ste_ldata.ste_tx_list_paddr != 0)
			bus_dmamap_unload(sc->ste_cdata.ste_tx_list_tag,
			    sc->ste_cdata.ste_tx_list_map);
		if (sc->ste_ldata.ste_tx_list != NULL)
			bus_dmamem_free(sc->ste_cdata.ste_tx_list_tag,
			    sc->ste_ldata.ste_tx_list,
			    sc->ste_cdata.ste_tx_list_map);
		sc->ste_ldata.ste_tx_list = NULL;
		sc->ste_ldata.ste_tx_list_paddr = 0;
		bus_dma_tag_destroy(sc->ste_cdata.ste_tx_list_tag);
		sc->ste_cdata.ste_tx_list_tag = NULL;
	}
	/* Rx descriptor list. */
	if (sc->ste_cdata.ste_rx_list_tag != NULL) {
		if (sc->ste_ldata.ste_rx_list_paddr != 0)
			bus_dmamap_unload(sc->ste_cdata.ste_rx_list_tag,
			    sc->ste_cdata.ste_rx_list_map);
		if (sc->ste_ldata.ste_rx_list != NULL)
			bus_dmamem_free(sc->ste_cdata.ste_rx_list_tag,
			    sc->ste_ldata.ste_rx_list,
			    sc->ste_cdata.ste_rx_list_map);
		sc->ste_ldata.ste_rx_list = NULL;
		sc->ste_ldata.ste_rx_list_paddr = 0;
		bus_dma_tag_destroy(sc->ste_cdata.ste_rx_list_tag);
		sc->ste_cdata.ste_rx_list_tag = NULL;
	}
	if (sc->ste_cdata.ste_parent_tag != NULL) {
		bus_dma_tag_destroy(sc->ste_cdata.ste_parent_tag);
		sc->ste_cdata.ste_parent_tag = NULL;
	}
}