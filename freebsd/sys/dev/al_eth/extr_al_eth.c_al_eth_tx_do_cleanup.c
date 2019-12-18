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
typedef  size_t uint16_t ;
struct mbuf {int dummy; } ;
struct al_eth_tx_buffer {unsigned int tx_descs; int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * m; } ;
struct al_eth_ring {int ring_id; size_t next_to_clean; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_buf_tag; struct al_eth_tx_buffer* tx_buffer_info; int /*<<< orphan*/  dma_q; } ;

/* Variables and functions */
 size_t AL_ETH_TX_RING_IDX_NEXT (struct al_eth_ring*,size_t) ; 
 unsigned int al_eth_comp_tx_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_smp_data_memory_barrier () ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf_dbg (int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
al_eth_tx_do_cleanup(struct al_eth_ring *tx_ring)
{
	unsigned int total_done;
	uint16_t next_to_clean;
	int qid = tx_ring->ring_id;

	total_done = al_eth_comp_tx_get(tx_ring->dma_q);
	device_printf_dbg(tx_ring->dev,
	    "tx_poll: q %d total completed descs %x\n", qid, total_done);
	next_to_clean = tx_ring->next_to_clean;

	while (total_done != 0) {
		struct al_eth_tx_buffer *tx_info;
		struct mbuf *mbuf;

		tx_info = &tx_ring->tx_buffer_info[next_to_clean];
		/* stop if not all descriptors of the packet are completed */
		if (tx_info->tx_descs > total_done)
			break;

		mbuf = tx_info->m;

		tx_info->m = NULL;

		device_printf_dbg(tx_ring->dev,
		    "tx_poll: q %d mbuf %p completed\n", qid, mbuf);

		/* map is no longer required */
		bus_dmamap_unload(tx_ring->dma_buf_tag, tx_info->dma_map);

		m_freem(mbuf);
		total_done -= tx_info->tx_descs;
		next_to_clean = AL_ETH_TX_RING_IDX_NEXT(tx_ring, next_to_clean);
	}

	tx_ring->next_to_clean = next_to_clean;

	device_printf_dbg(tx_ring->dev, "tx_poll: q %d done next to clean %x\n",
	    qid, next_to_clean);

	/*
	 * need to make the rings circular update visible to
	 * al_eth_start_xmit() before checking for netif_queue_stopped().
	 */
	al_smp_data_memory_barrier();
}