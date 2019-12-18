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
typedef  int /*<<< orphan*/  u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_PCI_LINK_STATUS ; 
 int /*<<< orphan*/  IXGBE_READ_PCIE_WORD (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_set_pci_config_data_generic (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

s32 ixgbe_get_bus_info_generic(struct ixgbe_hw *hw)
{
	u16 link_status;

	DEBUGFUNC("ixgbe_get_bus_info_generic");

	/* Get the negotiated link width and speed from PCI config space */
	link_status = IXGBE_READ_PCIE_WORD(hw, IXGBE_PCI_LINK_STATUS);

	ixgbe_set_pci_config_data_generic(hw, link_status);

	return IXGBE_SUCCESS;
}