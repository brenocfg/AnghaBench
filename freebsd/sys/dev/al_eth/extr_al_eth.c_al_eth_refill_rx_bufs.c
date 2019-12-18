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
struct al_eth_rx_buffer {int /*<<< orphan*/  al_buf; } ;
struct al_eth_ring {size_t next_to_use; int /*<<< orphan*/  dma_q; struct al_eth_rx_buffer* rx_buffer_info; } ;
struct al_eth_adapter {int /*<<< orphan*/  dev; struct al_eth_ring* rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_RX_FLAGS_INT ; 
 size_t AL_ETH_RX_RING_IDX_NEXT (struct al_eth_ring*,size_t) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ __predict_true (unsigned int) ; 
 scalar_t__ al_eth_alloc_rx_buf (struct al_eth_adapter*,struct al_eth_ring*,struct al_eth_rx_buffer*) ; 
 int /*<<< orphan*/  al_eth_rx_buffer_action (int /*<<< orphan*/ ,unsigned int) ; 
 int al_eth_rx_buffer_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_udma_available_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,...) ; 

__attribute__((used)) static int
al_eth_refill_rx_bufs(struct al_eth_adapter *adapter, unsigned int qid,
    unsigned int num)
{
	struct al_eth_ring *rx_ring = &adapter->rx_ring[qid];
	uint16_t next_to_use;
	unsigned int i;

	next_to_use = rx_ring->next_to_use;

	for (i = 0; i < num; i++) {
		int rc;
		struct al_eth_rx_buffer *rx_info =
		    &rx_ring->rx_buffer_info[next_to_use];

		if (__predict_false(al_eth_alloc_rx_buf(adapter,
		    rx_ring, rx_info) < 0)) {
			device_printf(adapter->dev,
			    "failed to alloc buffer for rx queue %d\n", qid);
			break;
		}

		rc = al_eth_rx_buffer_add(rx_ring->dma_q,
		    &rx_info->al_buf, AL_ETH_RX_FLAGS_INT, NULL);
		if (__predict_false(rc)) {
			device_printf(adapter->dev,
			    "failed to add buffer for rx queue %d\n", qid);
			break;
		}

		next_to_use = AL_ETH_RX_RING_IDX_NEXT(rx_ring, next_to_use);
	}

	if (__predict_false(i < num))
		device_printf(adapter->dev,
		    "refilled rx queue %d with %d pages only - available %d\n",
		    qid, i, al_udma_available_get(rx_ring->dma_q));

	if (__predict_true(i))
		al_eth_rx_buffer_action(rx_ring->dma_q, i);

	rx_ring->next_to_use = next_to_use;

	return (i);
}