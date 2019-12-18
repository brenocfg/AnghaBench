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
struct rt_softc_rx_ring {int /*<<< orphan*/ * data_dma_tag; int /*<<< orphan*/ * spare_dma_map; struct rt_softc_rx_data* data; int /*<<< orphan*/ * desc_dma_tag; int /*<<< orphan*/ * desc_dma_map; int /*<<< orphan*/ * desc; } ;
struct rt_softc_rx_data {int /*<<< orphan*/ * dma_map; int /*<<< orphan*/ * m; } ;
struct rt_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int RT_SOFTC_RX_RING_DATA_COUNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt_free_rx_ring(struct rt_softc *sc, struct rt_softc_rx_ring *ring)
{
	struct rt_softc_rx_data *data;
	int i;

	if (ring->desc != NULL) {
		bus_dmamap_sync(ring->desc_dma_tag, ring->desc_dma_map,
			BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(ring->desc_dma_tag, ring->desc_dma_map);
		bus_dmamem_free(ring->desc_dma_tag, ring->desc,
			ring->desc_dma_map);
	}

	if (ring->desc_dma_tag != NULL)
		bus_dma_tag_destroy(ring->desc_dma_tag);

	for (i = 0; i < RT_SOFTC_RX_RING_DATA_COUNT; i++) {
		data = &ring->data[i];

		if (data->m != NULL) {
			bus_dmamap_sync(ring->data_dma_tag, data->dma_map,
				BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(ring->data_dma_tag, data->dma_map);
			m_freem(data->m);
		}

		if (data->dma_map != NULL)
			bus_dmamap_destroy(ring->data_dma_tag, data->dma_map);
	}

	if (ring->spare_dma_map != NULL)
		bus_dmamap_destroy(ring->data_dma_tag, ring->spare_dma_map);

	if (ring->data_dma_tag != NULL)
		bus_dma_tag_destroy(ring->data_dma_tag);
}