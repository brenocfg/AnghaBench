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
struct ena_tx_buffer {int head_mapped; int seg_mapped; int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  map_seg; int /*<<< orphan*/  map_head; } ;
struct ena_ring {int ring_size; struct ena_tx_buffer* tx_buffer_info; } ;
struct ena_adapter {int /*<<< orphan*/  tx_buf_tag; int /*<<< orphan*/  pdev; struct ena_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  ENA_DBG ; 
 int /*<<< orphan*/  ENA_RING_MTX_LOCK (struct ena_ring*) ; 
 int /*<<< orphan*/  ENA_RING_MTX_UNLOCK (struct ena_ring*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  m_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ena_free_tx_bufs(struct ena_adapter *adapter, unsigned int qid)
{
	bool print_once = true;
	struct ena_ring *tx_ring = &adapter->tx_ring[qid];

	ENA_RING_MTX_LOCK(tx_ring);
	for (int i = 0; i < tx_ring->ring_size; i++) {
		struct ena_tx_buffer *tx_info = &tx_ring->tx_buffer_info[i];

		if (tx_info->mbuf == NULL)
			continue;

		if (print_once) {
			device_printf(adapter->pdev,
			    "free uncompleted tx mbuf qid %d idx 0x%x\n",
			    qid, i);
			print_once = false;
		} else {
			ena_trace(ENA_DBG,
			    "free uncompleted tx mbuf qid %d idx 0x%x\n",
			     qid, i);
		}

		if (tx_info->head_mapped == true) {
			bus_dmamap_sync(adapter->tx_buf_tag, tx_info->map_head,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(adapter->tx_buf_tag,
			    tx_info->map_head);
			tx_info->head_mapped = false;
		}

		if (tx_info->seg_mapped == true) {
			bus_dmamap_sync(adapter->tx_buf_tag, tx_info->map_seg,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(adapter->tx_buf_tag,
			    tx_info->map_seg);
			tx_info->seg_mapped = false;
		}

		m_free(tx_info->mbuf);
		tx_info->mbuf = NULL;
	}
	ENA_RING_MTX_UNLOCK(tx_ring);
}