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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_eth_adapter {scalar_t__ board_type; scalar_t__ internal_pcie_base; } ;

/* Variables and functions */
 scalar_t__ ALPINE_FPGA_NIC ; 
 scalar_t__ ALPINE_NIC ; 
 int /*<<< orphan*/  AL_DIS_FORWARD_INTR ; 
 int AL_REG_OFFSET_FORWARD_INTR ; 
 int /*<<< orphan*/  al_eth_forward_int_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_interrupts_mask (struct al_eth_adapter*) ; 

__attribute__((used)) static void
al_eth_disable_int_sync(struct al_eth_adapter *adapter)
{

	/* disable forwarding interrupts from eth through pci end point */
	if ((adapter->board_type == ALPINE_FPGA_NIC) ||
	    (adapter->board_type == ALPINE_NIC)) {
		al_eth_forward_int_config((uint32_t*)adapter->internal_pcie_base +
		    AL_REG_OFFSET_FORWARD_INTR, AL_DIS_FORWARD_INTR);
	}

	/* mask hw interrupts */
	al_eth_interrupts_mask(adapter);
}