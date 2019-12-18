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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  flags; } ;
struct ixgbe_hw {int /*<<< orphan*/  hw_addr; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IXGBE_CTRL ; 
 int /*<<< orphan*/  IXGBE_CTRL_GIO_DIS ; 
 int /*<<< orphan*/  IXGBE_ERROR_POLLING ; 
 int /*<<< orphan*/  IXGBE_ERR_MASTER_REQUESTS_PENDING ; 
 int /*<<< orphan*/  IXGBE_FLAGS_DOUBLE_RESET_REQUIRED ; 
 int /*<<< orphan*/  IXGBE_PCI_DEVICE_STATUS ; 
 int IXGBE_PCI_DEVICE_STATUS_TRANSACTION_PENDING ; 
 scalar_t__ IXGBE_PCI_MASTER_DISABLE_TIMEOUT ; 
 int IXGBE_READ_PCIE_WORD (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_REMOVED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_STATUS ; 
 int IXGBE_STATUS_GIO ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_X550 ; 
 scalar_t__ ixgbe_pcie_timeout_poll (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 ixgbe_disable_pcie_master(struct ixgbe_hw *hw)
{
	s32 status = IXGBE_SUCCESS;
	u32 i, poll;
	u16 value;

	DEBUGFUNC("ixgbe_disable_pcie_master");

	/* Always set this bit to ensure any future transactions are blocked */
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, IXGBE_CTRL_GIO_DIS);

	/* Exit if master requests are blocked */
	if (!(IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_GIO) ||
	    IXGBE_REMOVED(hw->hw_addr))
		goto out;

	/* Poll for master request bit to clear */
	for (i = 0; i < IXGBE_PCI_MASTER_DISABLE_TIMEOUT; i++) {
		usec_delay(100);
		if (!(IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_GIO))
			goto out;
	}

	/*
	 * Two consecutive resets are required via CTRL.RST per datasheet
	 * 5.2.5.3.2 Master Disable.  We set a flag to inform the reset routine
	 * of this need.  The first reset prevents new master requests from
	 * being issued by our device.  We then must wait 1usec or more for any
	 * remaining completions from the PCIe bus to trickle in, and then reset
	 * again to clear out any effects they may have had on our device.
	 */
	DEBUGOUT("GIO Master Disable bit didn't clear - requesting resets\n");
	hw->mac.flags |= IXGBE_FLAGS_DOUBLE_RESET_REQUIRED;

	if (hw->mac.type >= ixgbe_mac_X550)
		goto out;

	/*
	 * Before proceeding, make sure that the PCIe block does not have
	 * transactions pending.
	 */
	poll = ixgbe_pcie_timeout_poll(hw);
	for (i = 0; i < poll; i++) {
		usec_delay(100);
		value = IXGBE_READ_PCIE_WORD(hw, IXGBE_PCI_DEVICE_STATUS);
		if (IXGBE_REMOVED(hw->hw_addr))
			goto out;
		if (!(value & IXGBE_PCI_DEVICE_STATUS_TRANSACTION_PENDING))
			goto out;
	}

	ERROR_REPORT1(IXGBE_ERROR_POLLING,
		     "PCIe transaction pending bit also did not clear.\n");
	status = IXGBE_ERR_MASTER_REQUESTS_PENDING;

out:
	return status;
}