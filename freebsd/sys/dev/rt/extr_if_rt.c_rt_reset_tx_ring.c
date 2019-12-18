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
struct rt_txdesc {scalar_t__ sdl1; scalar_t__ sdl0; } ;
struct rt_softc_tx_ring {scalar_t__ data_next; scalar_t__ data_cur; scalar_t__ data_queued; int /*<<< orphan*/  data_dma_tag; struct rt_softc_tx_data* data; int /*<<< orphan*/  seg0_dma_map; int /*<<< orphan*/  seg0_dma_tag; int /*<<< orphan*/  desc_dma_map; int /*<<< orphan*/  desc_dma_tag; scalar_t__ desc_next; scalar_t__ desc_cur; scalar_t__ desc_queued; struct rt_txdesc* desc; } ;
struct rt_softc_tx_data {int /*<<< orphan*/ * m; int /*<<< orphan*/  dma_map; } ;
struct rt_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int RT_SOFTC_TX_RING_DATA_COUNT ; 
 int RT_SOFTC_TX_RING_DESC_COUNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rt_reset_tx_ring(struct rt_softc *sc, struct rt_softc_tx_ring *ring)
{
	struct rt_softc_tx_data *data;
	struct rt_txdesc *desc;
	int i;

	for (i = 0; i < RT_SOFTC_TX_RING_DESC_COUNT; i++) {
		desc = &ring->desc[i];

		desc->sdl0 = 0;
		desc->sdl1 = 0;
	}

	ring->desc_queued = 0;
	ring->desc_cur = 0;
	ring->desc_next = 0;

	bus_dmamap_sync(ring->desc_dma_tag, ring->desc_dma_map,
		BUS_DMASYNC_PREWRITE);

	bus_dmamap_sync(ring->seg0_dma_tag, ring->seg0_dma_map,
		BUS_DMASYNC_PREWRITE);

	for (i = 0; i < RT_SOFTC_TX_RING_DATA_COUNT; i++) {
		data = &ring->data[i];

		if (data->m != NULL) {
			bus_dmamap_sync(ring->data_dma_tag, data->dma_map,
				BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(ring->data_dma_tag, data->dma_map);
			m_freem(data->m);
			data->m = NULL;
		}
	}

	ring->data_queued = 0;
	ring->data_cur = 0;
	ring->data_next = 0;
}