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
struct unit_regs {int dummy; } ;
struct al_eth_ring {int ring_id; int unmask_val; void* unmask_reg_offset; int /*<<< orphan*/  hw_count; int /*<<< orphan*/  sw_count; int /*<<< orphan*/  dma_q; int /*<<< orphan*/  netdev; struct al_eth_adapter* adapter; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_udma; int /*<<< orphan*/  tx_udma; } ;
struct al_eth_adapter {int num_tx_queues; int num_rx_queues; scalar_t__ udma_base; int /*<<< orphan*/  rx_descs_count; int /*<<< orphan*/  rx_ring_count; TYPE_1__ hal_adapter; int /*<<< orphan*/  netdev; int /*<<< orphan*/  dev; struct al_eth_ring* rx_ring; int /*<<< orphan*/  tx_descs_count; int /*<<< orphan*/  tx_ring_count; struct al_eth_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_INT_GROUP_B ; 
 int /*<<< orphan*/  AL_INT_GROUP_C ; 
 int /*<<< orphan*/  AL_UDMA_IOFIC_LEVEL_PRIMARY ; 
 void* al_udma_iofic_unmask_offset_get (struct unit_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_udma_q_handle_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
al_eth_init_rings(struct al_eth_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_tx_queues; i++) {
		struct al_eth_ring *ring = &adapter->tx_ring[i];

		ring->ring_id = i;
		ring->dev = adapter->dev;
		ring->adapter = adapter;
		ring->netdev = adapter->netdev;
		al_udma_q_handle_get(&adapter->hal_adapter.tx_udma, i,
		    &ring->dma_q);
		ring->sw_count = adapter->tx_ring_count;
		ring->hw_count = adapter->tx_descs_count;
		ring->unmask_reg_offset = al_udma_iofic_unmask_offset_get((struct unit_regs *)adapter->udma_base, AL_UDMA_IOFIC_LEVEL_PRIMARY, AL_INT_GROUP_C);
		ring->unmask_val = ~(1 << i);
	}

	for (i = 0; i < adapter->num_rx_queues; i++) {
		struct al_eth_ring *ring = &adapter->rx_ring[i];

		ring->ring_id = i;
		ring->dev = adapter->dev;
		ring->adapter = adapter;
		ring->netdev = adapter->netdev;
		al_udma_q_handle_get(&adapter->hal_adapter.rx_udma, i, &ring->dma_q);
		ring->sw_count = adapter->rx_ring_count;
		ring->hw_count = adapter->rx_descs_count;
		ring->unmask_reg_offset = al_udma_iofic_unmask_offset_get(
		    (struct unit_regs *)adapter->udma_base,
		    AL_UDMA_IOFIC_LEVEL_PRIMARY, AL_INT_GROUP_B);
		ring->unmask_val = ~(1 << i);
	}
}