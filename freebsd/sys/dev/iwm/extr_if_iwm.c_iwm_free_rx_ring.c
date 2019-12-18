#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwm_softc {TYPE_1__* cfg; } ;
struct iwm_rx_ring {int /*<<< orphan*/ * data_dmat; int /*<<< orphan*/ * spare_map; struct iwm_rx_data* data; int /*<<< orphan*/  used_desc_dma; int /*<<< orphan*/  stat_dma; int /*<<< orphan*/  free_desc_dma; } ;
struct iwm_rx_data {int /*<<< orphan*/ * map; int /*<<< orphan*/ * m; } ;
struct TYPE_2__ {scalar_t__ mqrx_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int IWM_RX_LEGACY_RING_COUNT ; 
 int IWM_RX_MQ_RING_COUNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_dma_contig_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iwm_free_rx_ring(struct iwm_softc *sc, struct iwm_rx_ring *ring)
{
	int count, i;

	iwm_dma_contig_free(&ring->free_desc_dma);
	iwm_dma_contig_free(&ring->stat_dma);
	iwm_dma_contig_free(&ring->used_desc_dma);

	count = sc->cfg->mqrx_supported ? IWM_RX_MQ_RING_COUNT :
	    IWM_RX_LEGACY_RING_COUNT;

	for (i = 0; i < count; i++) {
		struct iwm_rx_data *data = &ring->data[i];

		if (data->m != NULL) {
			bus_dmamap_sync(ring->data_dmat, data->map,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(ring->data_dmat, data->map);
			m_freem(data->m);
			data->m = NULL;
		}
		if (data->map != NULL) {
			bus_dmamap_destroy(ring->data_dmat, data->map);
			data->map = NULL;
		}
	}
	if (ring->spare_map != NULL) {
		bus_dmamap_destroy(ring->data_dmat, ring->spare_map);
		ring->spare_map = NULL;
	}
	if (ring->data_dmat != NULL) {
		bus_dma_tag_destroy(ring->data_dmat);
		ring->data_dmat = NULL;
	}
}