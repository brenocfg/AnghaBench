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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  arc_subsystem_valid; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_ERR_HOST_INTERFACE_COMMAND ; 
 int /*<<< orphan*/  E1000_HICR ; 
 int E1000_HICR_C ; 
 int E1000_HICR_EN ; 
 scalar_t__ E1000_MNG_DHCP_COMMAND_TIMEOUT ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  msec_delay_irq (int) ; 

s32 e1000_mng_enable_host_if_generic(struct e1000_hw *hw)
{
	u32 hicr;
	u8 i;

	DEBUGFUNC("e1000_mng_enable_host_if_generic");

	if (!hw->mac.arc_subsystem_valid) {
		DEBUGOUT("ARC subsystem not valid.\n");
		return -E1000_ERR_HOST_INTERFACE_COMMAND;
	}

	/* Check that the host interface is enabled. */
	hicr = E1000_READ_REG(hw, E1000_HICR);
	if (!(hicr & E1000_HICR_EN)) {
		DEBUGOUT("E1000_HOST_EN bit disabled.\n");
		return -E1000_ERR_HOST_INTERFACE_COMMAND;
	}
	/* check the previous command is completed */
	for (i = 0; i < E1000_MNG_DHCP_COMMAND_TIMEOUT; i++) {
		hicr = E1000_READ_REG(hw, E1000_HICR);
		if (!(hicr & E1000_HICR_C))
			break;
		msec_delay_irq(1);
	}

	if (i == E1000_MNG_DHCP_COMMAND_TIMEOUT) {
		DEBUGOUT("Previous command timeout failed .\n");
		return -E1000_ERR_HOST_INTERFACE_COMMAND;
	}

	return E1000_SUCCESS;
}