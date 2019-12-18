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
struct TYPE_4__ {int /*<<< orphan*/  (* set_lan_id ) (struct ixgbe_hw*) ;} ;
struct ixgbe_mac_info {TYPE_2__ ops; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  speed; int /*<<< orphan*/  width; } ;
struct ixgbe_hw {TYPE_1__ bus; struct ixgbe_mac_info mac; } ;

/* Variables and functions */
 int IXGBE_PCI_LINK_SPEED ; 
#define  IXGBE_PCI_LINK_SPEED_2500 134 
#define  IXGBE_PCI_LINK_SPEED_5000 133 
#define  IXGBE_PCI_LINK_SPEED_8000 132 
 int IXGBE_PCI_LINK_WIDTH ; 
#define  IXGBE_PCI_LINK_WIDTH_1 131 
#define  IXGBE_PCI_LINK_WIDTH_2 130 
#define  IXGBE_PCI_LINK_WIDTH_4 129 
#define  IXGBE_PCI_LINK_WIDTH_8 128 
 int /*<<< orphan*/  ixgbe_bus_speed_2500 ; 
 int /*<<< orphan*/  ixgbe_bus_speed_5000 ; 
 int /*<<< orphan*/  ixgbe_bus_speed_8000 ; 
 int /*<<< orphan*/  ixgbe_bus_speed_unknown ; 
 scalar_t__ ixgbe_bus_type_pci_express ; 
 scalar_t__ ixgbe_bus_type_unknown ; 
 int /*<<< orphan*/  ixgbe_bus_width_pcie_x1 ; 
 int /*<<< orphan*/  ixgbe_bus_width_pcie_x2 ; 
 int /*<<< orphan*/  ixgbe_bus_width_pcie_x4 ; 
 int /*<<< orphan*/  ixgbe_bus_width_pcie_x8 ; 
 int /*<<< orphan*/  ixgbe_bus_width_unknown ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 

void ixgbe_set_pci_config_data_generic(struct ixgbe_hw *hw, u16 link_status)
{
	struct ixgbe_mac_info *mac = &hw->mac;

	if (hw->bus.type == ixgbe_bus_type_unknown)
		hw->bus.type = ixgbe_bus_type_pci_express;

	switch (link_status & IXGBE_PCI_LINK_WIDTH) {
	case IXGBE_PCI_LINK_WIDTH_1:
		hw->bus.width = ixgbe_bus_width_pcie_x1;
		break;
	case IXGBE_PCI_LINK_WIDTH_2:
		hw->bus.width = ixgbe_bus_width_pcie_x2;
		break;
	case IXGBE_PCI_LINK_WIDTH_4:
		hw->bus.width = ixgbe_bus_width_pcie_x4;
		break;
	case IXGBE_PCI_LINK_WIDTH_8:
		hw->bus.width = ixgbe_bus_width_pcie_x8;
		break;
	default:
		hw->bus.width = ixgbe_bus_width_unknown;
		break;
	}

	switch (link_status & IXGBE_PCI_LINK_SPEED) {
	case IXGBE_PCI_LINK_SPEED_2500:
		hw->bus.speed = ixgbe_bus_speed_2500;
		break;
	case IXGBE_PCI_LINK_SPEED_5000:
		hw->bus.speed = ixgbe_bus_speed_5000;
		break;
	case IXGBE_PCI_LINK_SPEED_8000:
		hw->bus.speed = ixgbe_bus_speed_8000;
		break;
	default:
		hw->bus.speed = ixgbe_bus_speed_unknown;
		break;
	}

	mac->ops.set_lan_id(hw);
}