#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct mbuf {int dummy; } ;
struct al_eth_pkt {int num_of_bufs; struct al_buf* bufs; int /*<<< orphan*/  flags; } ;
struct al_eth_tx_buffer {scalar_t__ tx_descs; int /*<<< orphan*/  dma_map; struct al_eth_pkt hal_pkt; struct mbuf* m; } ;
struct al_eth_ring {int stall; int ring_id; size_t next_to_use; int /*<<< orphan*/  dma_q; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_buf_tag; struct al_eth_tx_buffer* tx_buffer_info; } ;
struct al_buf {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ AL_ETH_DEFAULT_TX_HW_DESCS ; 
 int AL_ETH_PKT_MAX_BUFS ; 
 int /*<<< orphan*/  AL_ETH_TX_FLAGS_INT ; 
 size_t AL_ETH_TX_RING_IDX_NEXT (struct al_eth_ring*,size_t) ; 
 scalar_t__ AL_ETH_TX_WAKEUP_THRESH ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int EFBIG ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ TRUE ; 
 int XMIT_QUEUE_TIMEOUT ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  al_data_memory_barrier () ; 
 int /*<<< orphan*/  al_eth_tx_csum (struct al_eth_ring*,struct al_eth_tx_buffer*,struct al_eth_pkt*,struct mbuf*) ; 
 int /*<<< orphan*/  al_eth_tx_dma_action (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ al_eth_tx_pkt_prepare (int /*<<< orphan*/ ,struct al_eth_pkt*) ; 
 int al_udma_available_get (int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_printf_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
al_eth_xmit_mbuf(struct al_eth_ring *tx_ring, struct mbuf *m)
{
	struct al_eth_tx_buffer *tx_info;
	int error;
	int nsegs, a;
	uint16_t next_to_use;
	bus_dma_segment_t segs[AL_ETH_PKT_MAX_BUFS + 1];
	struct al_eth_pkt *hal_pkt;
	struct al_buf *al_buf;
	boolean_t remap;

	/* Check if queue is ready */
	if (unlikely(tx_ring->stall) != 0) {
		for (a = 0; a < XMIT_QUEUE_TIMEOUT; a++) {
			if (al_udma_available_get(tx_ring->dma_q) >=
			    (AL_ETH_DEFAULT_TX_HW_DESCS -
			    AL_ETH_TX_WAKEUP_THRESH)) {
				tx_ring->stall = 0;
				break;
			}
			pause("stall", 1);
		}
		if (a == XMIT_QUEUE_TIMEOUT) {
			device_printf(tx_ring->dev,
			    "timeout waiting for queue %d ready!\n",
			    tx_ring->ring_id);
			return;
		} else {
			device_printf_dbg(tx_ring->dev,
			    "queue %d is ready!\n", tx_ring->ring_id);
		}
	}

	next_to_use = tx_ring->next_to_use;
	tx_info = &tx_ring->tx_buffer_info[next_to_use];
	tx_info->m = m;
	hal_pkt = &tx_info->hal_pkt;

	if (m == NULL) {
		device_printf(tx_ring->dev, "mbuf is NULL\n");
		return;
	}

	remap = TRUE;
	/* Map packets for DMA */
retry:
	error = bus_dmamap_load_mbuf_sg(tx_ring->dma_buf_tag, tx_info->dma_map,
	    m, segs, &nsegs, BUS_DMA_NOWAIT);
	if (__predict_false(error)) {
		struct mbuf *m_new;

		if (error == EFBIG) {
			/* Try it again? - one try */
			if (remap == TRUE) {
				remap = FALSE;
				m_new = m_defrag(m, M_NOWAIT);
				if (m_new == NULL) {
					device_printf(tx_ring->dev,
					    "failed to defrag mbuf\n");
					goto exit;
				}
				m = m_new;
				goto retry;
			} else {
				device_printf(tx_ring->dev,
				    "failed to map mbuf, error %d\n", error);
				goto exit;
			}
		} else {
			device_printf(tx_ring->dev,
			    "failed to map mbuf, error %d\n", error);
			goto exit;
		}
	}

	/* set flags and meta data */
	hal_pkt->flags = AL_ETH_TX_FLAGS_INT;
	al_eth_tx_csum(tx_ring, tx_info, hal_pkt, m);

	al_buf = hal_pkt->bufs;
	for (a = 0; a < nsegs; a++) {
		al_buf->addr = segs[a].ds_addr;
		al_buf->len = segs[a].ds_len;

		al_buf++;
	}

	hal_pkt->num_of_bufs = nsegs;

	/* prepare the packet's descriptors to dma engine */
	tx_info->tx_descs = al_eth_tx_pkt_prepare(tx_ring->dma_q, hal_pkt);

	if (tx_info->tx_descs == 0)
		goto exit;

	/*
	 * stop the queue when no more space available, the packet can have up
	 * to AL_ETH_PKT_MAX_BUFS + 1 buffers and a meta descriptor
	 */
	if (unlikely(al_udma_available_get(tx_ring->dma_q) <
	    (AL_ETH_PKT_MAX_BUFS + 2))) {
		tx_ring->stall = 1;
		device_printf_dbg(tx_ring->dev, "stall, stopping queue %d...\n",
		    tx_ring->ring_id);
		al_data_memory_barrier();
	}

	tx_ring->next_to_use = AL_ETH_TX_RING_IDX_NEXT(tx_ring, next_to_use);

	/* trigger the dma engine */
	al_eth_tx_dma_action(tx_ring->dma_q, tx_info->tx_descs);
	return;

exit:
	m_freem(m);
}