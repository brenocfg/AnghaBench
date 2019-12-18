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
struct al_udma_q_params {int /*<<< orphan*/ * desc_base; int /*<<< orphan*/  desc_phy_base_map; int /*<<< orphan*/  desc_phy_base_tag; } ;
struct al_eth_ring {int sw_count; int /*<<< orphan*/  br_mtx; TYPE_1__* tx_buffer_info; int /*<<< orphan*/  dma_buf_tag; int /*<<< orphan*/ * br; int /*<<< orphan*/  enqueue_tq; int /*<<< orphan*/  enqueue_task; int /*<<< orphan*/  cmpl_tq; int /*<<< orphan*/  cmpl_task; struct al_udma_q_params q_params; } ;
struct al_eth_adapter {int /*<<< orphan*/  netdev; struct al_eth_ring* tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * m; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_IFAL ; 
 int /*<<< orphan*/  al_dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbr_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ taskqueue_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
al_eth_free_tx_resources(struct al_eth_adapter *adapter, int qid)
{
	struct al_eth_ring *tx_ring = &adapter->tx_ring[qid];
	struct al_udma_q_params *q_params = &tx_ring->q_params;
	int size;

	/* At this point interrupts' handlers must be deactivated */
	while (taskqueue_cancel(tx_ring->cmpl_tq, &tx_ring->cmpl_task, NULL))
		taskqueue_drain(tx_ring->cmpl_tq, &tx_ring->cmpl_task);

	taskqueue_free(tx_ring->cmpl_tq);
	while (taskqueue_cancel(tx_ring->enqueue_tq,
	    &tx_ring->enqueue_task, NULL)) {
		taskqueue_drain(tx_ring->enqueue_tq, &tx_ring->enqueue_task);
	}

	taskqueue_free(tx_ring->enqueue_tq);

	if (tx_ring->br != NULL) {
		drbr_flush(adapter->netdev, tx_ring->br);
		buf_ring_free(tx_ring->br, M_DEVBUF);
	}

	for (size = 0; size < tx_ring->sw_count; size++) {
		m_freem(tx_ring->tx_buffer_info[size].m);
		tx_ring->tx_buffer_info[size].m = NULL;

		bus_dmamap_unload(tx_ring->dma_buf_tag,
		    tx_ring->tx_buffer_info[size].dma_map);
		bus_dmamap_destroy(tx_ring->dma_buf_tag,
		    tx_ring->tx_buffer_info[size].dma_map);
	}
	bus_dma_tag_destroy(tx_ring->dma_buf_tag);

	free(tx_ring->tx_buffer_info, M_IFAL);
	tx_ring->tx_buffer_info = NULL;

	mtx_destroy(&tx_ring->br_mtx);

	/* if not set, then don't free */
	if (q_params->desc_base == NULL)
		return;

	al_dma_free_coherent(q_params->desc_phy_base_tag,
	    q_params->desc_phy_base_map, q_params->desc_base);

	q_params->desc_base = NULL;
}