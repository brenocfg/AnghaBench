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
struct al_udma_q_params {scalar_t__ cdesc_phy_base; int /*<<< orphan*/ * cdesc_base; int /*<<< orphan*/  cdesc_phy_base_map; int /*<<< orphan*/  cdesc_phy_base_tag; int /*<<< orphan*/ * desc_base; int /*<<< orphan*/  desc_phy_base_map; int /*<<< orphan*/  desc_phy_base_tag; } ;
struct al_eth_ring {int sw_count; int /*<<< orphan*/  lro; TYPE_1__* rx_buffer_info; int /*<<< orphan*/  dma_buf_tag; int /*<<< orphan*/  enqueue_tq; int /*<<< orphan*/  enqueue_task; struct al_udma_q_params q_params; } ;
struct al_eth_adapter {struct al_eth_ring* rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * m; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IFAL ; 
 int /*<<< orphan*/  al_dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 scalar_t__ taskqueue_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_lro_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
al_eth_free_rx_resources(struct al_eth_adapter *adapter, unsigned int qid)
{
	struct al_eth_ring *rx_ring = &adapter->rx_ring[qid];
	struct al_udma_q_params *q_params = &rx_ring->q_params;
	int size;

	/* At this point interrupts' handlers must be deactivated */
	while (taskqueue_cancel(rx_ring->enqueue_tq,
	    &rx_ring->enqueue_task, NULL)) {
		taskqueue_drain(rx_ring->enqueue_tq, &rx_ring->enqueue_task);
	}

	taskqueue_free(rx_ring->enqueue_tq);

	for (size = 0; size < rx_ring->sw_count; size++) {
		m_freem(rx_ring->rx_buffer_info[size].m);
		rx_ring->rx_buffer_info[size].m = NULL;
		bus_dmamap_unload(rx_ring->dma_buf_tag,
		    rx_ring->rx_buffer_info[size].dma_map);
		bus_dmamap_destroy(rx_ring->dma_buf_tag,
		    rx_ring->rx_buffer_info[size].dma_map);
	}
	bus_dma_tag_destroy(rx_ring->dma_buf_tag);

	free(rx_ring->rx_buffer_info, M_IFAL);
	rx_ring->rx_buffer_info = NULL;

	/* if not set, then don't free */
	if (q_params->desc_base == NULL)
		return;

	al_dma_free_coherent(q_params->desc_phy_base_tag,
	    q_params->desc_phy_base_map, q_params->desc_base);

	q_params->desc_base = NULL;

	/* if not set, then don't free */
	if (q_params->cdesc_base == NULL)
		return;

	al_dma_free_coherent(q_params->cdesc_phy_base_tag,
	    q_params->cdesc_phy_base_map, q_params->cdesc_base);

	q_params->cdesc_phy_base = 0;

	/* Free LRO resources */
	tcp_lro_free(&rx_ring->lro);
}