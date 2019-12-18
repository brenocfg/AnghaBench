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
struct rt2860_tx_data {int /*<<< orphan*/  map; } ;
struct rt2860_softc {int /*<<< orphan*/  data_pool; int /*<<< orphan*/ * txwi_dmat; int /*<<< orphan*/  txwi_map; int /*<<< orphan*/ * txwi_vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct rt2860_tx_data* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

void
rt2860_free_tx_pool(struct rt2860_softc *sc)
{
	if (sc->txwi_vaddr != NULL) {
		bus_dmamap_sync(sc->txwi_dmat, sc->txwi_map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->txwi_dmat, sc->txwi_map);
		bus_dmamem_free(sc->txwi_dmat, sc->txwi_vaddr, sc->txwi_map);
	}
	if (sc->txwi_dmat != NULL)
		bus_dma_tag_destroy(sc->txwi_dmat);

	while (!SLIST_EMPTY(&sc->data_pool)) {
		struct rt2860_tx_data *data;
		data = SLIST_FIRST(&sc->data_pool);
		bus_dmamap_destroy(sc->txwi_dmat, data->map);
		SLIST_REMOVE_HEAD(&sc->data_pool, next);
	}
}