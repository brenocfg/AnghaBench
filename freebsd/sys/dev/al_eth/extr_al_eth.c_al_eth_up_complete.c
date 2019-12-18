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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_eth_adapter {scalar_t__ board_type; int /*<<< orphan*/  hal_adapter; int /*<<< orphan*/  stats_mtx; int /*<<< orphan*/  stats_callout; scalar_t__ internal_pcie_base; TYPE_1__* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_mtu; } ;

/* Variables and functions */
 scalar_t__ ALPINE_FPGA_NIC ; 
 scalar_t__ ALPINE_NIC ; 
 int /*<<< orphan*/  AL_EN_FORWARD_INTR ; 
 int AL_REG_OFFSET_FORWARD_INTR ; 
 int /*<<< orphan*/  al_eth_change_mtu (struct al_eth_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_config_rx_fwd (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_configure_int_mode (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_flow_ctrl_enable (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_forward_int_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_interrupts_unmask (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_mac_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_eth_refill_all_rx_bufs (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_udma_queues_enable_all (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_tick_stats ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
al_eth_up_complete(struct al_eth_adapter *adapter)
{

	al_eth_configure_int_mode(adapter);
	al_eth_config_rx_fwd(adapter);
	al_eth_change_mtu(adapter, adapter->netdev->if_mtu);
	al_eth_udma_queues_enable_all(adapter);
	al_eth_refill_all_rx_bufs(adapter);
	al_eth_interrupts_unmask(adapter);

	/* enable forwarding interrupts from eth through pci end point */
	if ((adapter->board_type == ALPINE_FPGA_NIC) ||
	    (adapter->board_type == ALPINE_NIC)) {
		al_eth_forward_int_config((uint32_t*)adapter->internal_pcie_base +
		    AL_REG_OFFSET_FORWARD_INTR, AL_EN_FORWARD_INTR);
	}

	al_eth_flow_ctrl_enable(adapter);

	mtx_lock(&adapter->stats_mtx);
	callout_reset(&adapter->stats_callout, hz, al_tick_stats, (void*)adapter);
	mtx_unlock(&adapter->stats_mtx);

	al_eth_mac_start(&adapter->hal_adapter);
}