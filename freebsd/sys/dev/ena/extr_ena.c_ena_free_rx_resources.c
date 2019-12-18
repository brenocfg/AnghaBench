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
struct ena_ring {int ring_size; TYPE_1__* free_rx_ids; TYPE_1__* rx_buffer_info; int /*<<< orphan*/  lro; } ;
struct ena_adapter {int /*<<< orphan*/  rx_buf_tag; struct ena_ring* rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; int /*<<< orphan*/ * mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_lro_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ena_free_rx_resources(struct ena_adapter *adapter, unsigned int qid)
{
	struct ena_ring *rx_ring = &adapter->rx_ring[qid];

	/* Free buffer DMA maps, */
	for (int i = 0; i < rx_ring->ring_size; i++) {
		bus_dmamap_sync(adapter->rx_buf_tag,
		    rx_ring->rx_buffer_info[i].map, BUS_DMASYNC_POSTREAD);
		m_freem(rx_ring->rx_buffer_info[i].mbuf);
		rx_ring->rx_buffer_info[i].mbuf = NULL;
		bus_dmamap_unload(adapter->rx_buf_tag,
		    rx_ring->rx_buffer_info[i].map);
		bus_dmamap_destroy(adapter->rx_buf_tag,
		    rx_ring->rx_buffer_info[i].map);
	}

	/* free LRO resources, */
	tcp_lro_free(&rx_ring->lro);

	/* free allocated memory */
	free(rx_ring->rx_buffer_info, M_DEVBUF);
	rx_ring->rx_buffer_info = NULL;

	free(rx_ring->free_rx_ids, M_DEVBUF);
	rx_ring->free_rx_ids = NULL;
}