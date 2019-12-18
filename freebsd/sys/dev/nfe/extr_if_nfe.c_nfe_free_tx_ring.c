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
struct nfe_tx_ring {int /*<<< orphan*/ * tx_desc_tag; int /*<<< orphan*/ * desc32; int /*<<< orphan*/ * desc64; int /*<<< orphan*/ * tx_desc_map; int /*<<< orphan*/ * tx_data_tag; struct nfe_tx_data* data; } ;
struct nfe_tx_data {int /*<<< orphan*/ * tx_data_map; int /*<<< orphan*/ * m; } ;
struct nfe_softc {int nfe_flags; } ;
struct nfe_desc64 {int dummy; } ;
struct nfe_desc32 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int NFE_40BIT_ADDR ; 
 int NFE_TX_RING_COUNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfe_free_tx_ring(struct nfe_softc *sc, struct nfe_tx_ring *ring)
{
	struct nfe_tx_data *data;
	void *desc;
	int i, descsize;

	if (sc->nfe_flags & NFE_40BIT_ADDR) {
		desc = ring->desc64;
		descsize = sizeof (struct nfe_desc64);
	} else {
		desc = ring->desc32;
		descsize = sizeof (struct nfe_desc32);
	}

	for (i = 0; i < NFE_TX_RING_COUNT; i++) {
		data = &ring->data[i];

		if (data->m != NULL) {
			bus_dmamap_sync(ring->tx_data_tag, data->tx_data_map,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(ring->tx_data_tag, data->tx_data_map);
			m_freem(data->m);
			data->m = NULL;
		}
		if (data->tx_data_map != NULL) {
			bus_dmamap_destroy(ring->tx_data_tag,
			    data->tx_data_map);
			data->tx_data_map = NULL;
		}
	}

	if (ring->tx_data_tag != NULL) {
		bus_dma_tag_destroy(ring->tx_data_tag);
		ring->tx_data_tag = NULL;
	}

	if (desc != NULL) {
		bus_dmamap_sync(ring->tx_desc_tag, ring->tx_desc_map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(ring->tx_desc_tag, ring->tx_desc_map);
		bus_dmamem_free(ring->tx_desc_tag, desc, ring->tx_desc_map);
		ring->desc64 = NULL;
		ring->desc32 = NULL;
		bus_dma_tag_destroy(ring->tx_desc_tag);
		ring->tx_desc_tag = NULL;
	}
}