#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct mbuf {int dummy; } ;
struct ena_tx_buffer {int head_mapped; int seg_mapped; scalar_t__ tx_descs; int /*<<< orphan*/  map_seg; int /*<<< orphan*/  map_head; int /*<<< orphan*/  timestamp; struct mbuf* mbuf; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue_wakeup; } ;
struct ena_ring {size_t next_to_clean; size_t* free_tx_ids; int running; int /*<<< orphan*/  enqueue_task; int /*<<< orphan*/  enqueue_tq; TYPE_3__ tx_stats; int /*<<< orphan*/  ena_com_io_sq; int /*<<< orphan*/  qid; int /*<<< orphan*/  ring_size; struct ena_tx_buffer* tx_buffer_info; TYPE_1__* que; } ;
struct ena_com_io_cq {int dummy; } ;
struct ena_adapter {TYPE_2__* ena_dev; int /*<<< orphan*/  tx_buf_tag; int /*<<< orphan*/  ifp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * io_sq_queues; struct ena_com_io_cq* io_cq_queues; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; struct ena_adapter* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int ENA_DBG ; 
 size_t ENA_IO_TXQ_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA_RING_MTX_LOCK (struct ena_ring*) ; 
 int /*<<< orphan*/  ENA_RING_MTX_UNLOCK (struct ena_ring*) ; 
 int ENA_TXPTH ; 
 int /*<<< orphan*/  ENA_TX_RESUME_THRESH ; 
 size_t ENA_TX_RING_IDX_NEXT (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ NM_IRQ_PASS ; 
 int TX_BUDGET ; 
 int TX_COMMIT ; 
 int /*<<< orphan*/  bintime_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ena_com_comp_ack (int /*<<< orphan*/ *,unsigned int) ; 
 int ena_com_sq_have_enough_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ena_com_tx_comp_req_id_get (struct ena_com_io_cq*,size_t*) ; 
 int /*<<< orphan*/  ena_com_update_dev_comp_head (struct ena_com_io_cq*) ; 
 int /*<<< orphan*/  ena_trace (int,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ netmap_tx_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int validate_tx_req_id (struct ena_ring*,size_t) ; 

__attribute__((used)) static int
ena_tx_cleanup(struct ena_ring *tx_ring)
{
	struct ena_adapter *adapter;
	struct ena_com_io_cq* io_cq;
	uint16_t next_to_clean;
	uint16_t req_id;
	uint16_t ena_qid;
	unsigned int total_done = 0;
	int rc;
	int commit = TX_COMMIT;
	int budget = TX_BUDGET;
	int work_done;
	bool above_thresh;

	adapter = tx_ring->que->adapter;
	ena_qid = ENA_IO_TXQ_IDX(tx_ring->que->id);
	io_cq = &adapter->ena_dev->io_cq_queues[ena_qid];
	next_to_clean = tx_ring->next_to_clean;

#ifdef DEV_NETMAP
	if (netmap_tx_irq(adapter->ifp, tx_ring->qid) != NM_IRQ_PASS)
		return (0);
#endif /* DEV_NETMAP */

	do {
		struct ena_tx_buffer *tx_info;
		struct mbuf *mbuf;

		rc = ena_com_tx_comp_req_id_get(io_cq, &req_id);
		if (unlikely(rc != 0))
			break;

		rc = validate_tx_req_id(tx_ring, req_id);
		if (unlikely(rc != 0))
			break;

		tx_info = &tx_ring->tx_buffer_info[req_id];

		mbuf = tx_info->mbuf;

		tx_info->mbuf = NULL;
		bintime_clear(&tx_info->timestamp);

		/* Map is no longer required */
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

		ena_trace(ENA_DBG | ENA_TXPTH, "tx: q %d mbuf %p completed\n",
		    tx_ring->qid, mbuf);

		m_freem(mbuf);

		total_done += tx_info->tx_descs;

		tx_ring->free_tx_ids[next_to_clean] = req_id;
		next_to_clean = ENA_TX_RING_IDX_NEXT(next_to_clean,
		    tx_ring->ring_size);

		if (unlikely(--commit == 0)) {
			commit = TX_COMMIT;
			/* update ring state every TX_COMMIT descriptor */
			tx_ring->next_to_clean = next_to_clean;
			ena_com_comp_ack(
			    &adapter->ena_dev->io_sq_queues[ena_qid],
			    total_done);
			ena_com_update_dev_comp_head(io_cq);
			total_done = 0;
		}
	} while (likely(--budget));

	work_done = TX_BUDGET - budget;

	ena_trace(ENA_DBG | ENA_TXPTH, "tx: q %d done. total pkts: %d\n",
	tx_ring->qid, work_done);

	/* If there is still something to commit update ring state */
	if (likely(commit != TX_COMMIT)) {
		tx_ring->next_to_clean = next_to_clean;
		ena_com_comp_ack(&adapter->ena_dev->io_sq_queues[ena_qid],
		    total_done);
		ena_com_update_dev_comp_head(io_cq);
	}

	/*
	 * Need to make the rings circular update visible to
	 * ena_xmit_mbuf() before checking for tx_ring->running.
	 */
	mb();

	above_thresh = ena_com_sq_have_enough_space(tx_ring->ena_com_io_sq,
	    ENA_TX_RESUME_THRESH);
	if (unlikely(!tx_ring->running && above_thresh)) {
		ENA_RING_MTX_LOCK(tx_ring);
		above_thresh =
		    ena_com_sq_have_enough_space(tx_ring->ena_com_io_sq,
		    ENA_TX_RESUME_THRESH);
		if (!tx_ring->running && above_thresh) {
			tx_ring->running = true;
			counter_u64_add(tx_ring->tx_stats.queue_wakeup, 1);
			taskqueue_enqueue(tx_ring->enqueue_tq,
			    &tx_ring->enqueue_task);
		}
		ENA_RING_MTX_UNLOCK(tx_ring);
	}

	return (work_done);
}