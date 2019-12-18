#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dma_txd_busaddr; scalar_t__ dma_txs_busaddr; scalar_t__ dma_rxd_busaddr; int /*<<< orphan*/ * dma_parent_tag; int /*<<< orphan*/ * rxd_base_dma; int /*<<< orphan*/ * dma_rxd_tag; int /*<<< orphan*/  dma_rxd_map; int /*<<< orphan*/ * txs_base; int /*<<< orphan*/ * dma_txs_tag; int /*<<< orphan*/  dma_txs_map; int /*<<< orphan*/ * txd_base; int /*<<< orphan*/ * dma_txd_tag; int /*<<< orphan*/  dma_txd_map; } ;
typedef  TYPE_1__ ae_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ae_dma_free(ae_softc_t *sc)
{

	if (sc->dma_txd_tag != NULL) {
		if (sc->dma_txd_busaddr != 0)
			bus_dmamap_unload(sc->dma_txd_tag, sc->dma_txd_map);
		if (sc->txd_base != NULL)
			bus_dmamem_free(sc->dma_txd_tag, sc->txd_base,
			    sc->dma_txd_map);
		bus_dma_tag_destroy(sc->dma_txd_tag);
		sc->dma_txd_tag = NULL;
		sc->txd_base = NULL;
		sc->dma_txd_busaddr = 0;
	}
	if (sc->dma_txs_tag != NULL) {
		if (sc->dma_txs_busaddr != 0)
			bus_dmamap_unload(sc->dma_txs_tag, sc->dma_txs_map);
		if (sc->txs_base != NULL)
			bus_dmamem_free(sc->dma_txs_tag, sc->txs_base,
			    sc->dma_txs_map);
		bus_dma_tag_destroy(sc->dma_txs_tag);
		sc->dma_txs_tag = NULL;
		sc->txs_base = NULL;
		sc->dma_txs_busaddr = 0;
	}
	if (sc->dma_rxd_tag != NULL) {
		if (sc->dma_rxd_busaddr != 0)
			bus_dmamap_unload(sc->dma_rxd_tag, sc->dma_rxd_map);
		if (sc->rxd_base_dma != NULL)
			bus_dmamem_free(sc->dma_rxd_tag, sc->rxd_base_dma,
			    sc->dma_rxd_map);
		bus_dma_tag_destroy(sc->dma_rxd_tag);
		sc->dma_rxd_tag = NULL;
		sc->rxd_base_dma = NULL;
		sc->dma_rxd_busaddr = 0;
	}
	if (sc->dma_parent_tag != NULL) {
		bus_dma_tag_destroy(sc->dma_parent_tag);
		sc->dma_parent_tag = NULL;
	}
}