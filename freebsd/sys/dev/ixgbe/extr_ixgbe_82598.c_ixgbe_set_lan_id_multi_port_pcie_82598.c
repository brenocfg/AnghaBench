#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* read ) (struct ixgbe_hw*,scalar_t__,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_bus_info {scalar_t__ func; } ;
struct ixgbe_hw {TYPE_2__ eeprom; struct ixgbe_bus_info bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_PCIE_CTRL2 ; 
 int IXGBE_PCIE_CTRL2_DISABLE_SELECT ; 
 int IXGBE_PCIE_CTRL2_DUMMY_ENABLE ; 
 int IXGBE_PCIE_CTRL2_LAN_DISABLE ; 
 scalar_t__ IXGBE_PCIE_GENERAL_PTR ; 
 int /*<<< orphan*/  ixgbe_set_lan_id_multi_port_pcie (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,scalar_t__,int*) ; 

void ixgbe_set_lan_id_multi_port_pcie_82598(struct ixgbe_hw *hw)
{
	struct ixgbe_bus_info *bus = &hw->bus;
	u16 pci_gen = 0;
	u16 pci_ctrl2 = 0;

	DEBUGFUNC("ixgbe_set_lan_id_multi_port_pcie_82598");

	ixgbe_set_lan_id_multi_port_pcie(hw);

	/* check if LAN0 is disabled */
	hw->eeprom.ops.read(hw, IXGBE_PCIE_GENERAL_PTR, &pci_gen);
	if ((pci_gen != 0) && (pci_gen != 0xFFFF)) {

		hw->eeprom.ops.read(hw, pci_gen + IXGBE_PCIE_CTRL2, &pci_ctrl2);

		/* if LAN0 is completely disabled force function to 0 */
		if ((pci_ctrl2 & IXGBE_PCIE_CTRL2_LAN_DISABLE) &&
		    !(pci_ctrl2 & IXGBE_PCIE_CTRL2_DISABLE_SELECT) &&
		    !(pci_ctrl2 & IXGBE_PCIE_CTRL2_DUMMY_ENABLE)) {

			bus->func = 0;
		}
	}
}