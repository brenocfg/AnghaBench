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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {int /*<<< orphan*/  hw_addr; TYPE_1__ bus; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_GIO_MASTER_DISABLE ; 
 scalar_t__ E1000_ERR_MASTER_REQUESTS_PENDING ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_REMOVED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_GIO_MASTER_ENABLE ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MASTER_DISABLE_TIMEOUT ; 
 scalar_t__ e1000_bus_type_pci_express ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 e1000_disable_pcie_master_generic(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 timeout = MASTER_DISABLE_TIMEOUT;

	DEBUGFUNC("e1000_disable_pcie_master_generic");

	if (hw->bus.type != e1000_bus_type_pci_express)
		return E1000_SUCCESS;

	ctrl = E1000_READ_REG(hw, E1000_CTRL);
	ctrl |= E1000_CTRL_GIO_MASTER_DISABLE;
	E1000_WRITE_REG(hw, E1000_CTRL, ctrl);

	while (timeout) {
		if (!(E1000_READ_REG(hw, E1000_STATUS) &
		      E1000_STATUS_GIO_MASTER_ENABLE) ||
				E1000_REMOVED(hw->hw_addr))
			break;
		usec_delay(100);
		timeout--;
	}

	if (!timeout) {
		DEBUGOUT("Master requests are pending.\n");
		return -E1000_ERR_MASTER_REQUESTS_PENDING;
	}

	return E1000_SUCCESS;
}