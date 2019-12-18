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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_lan_id ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {TYPE_1__ ops; } ;
struct e1000_bus_info {int width; void* speed; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_bus_info bus; struct e1000_mac_info mac; } ;
typedef  scalar_t__ s32 ;
typedef  enum e1000_bus_width { ____Placeholder_e1000_bus_width } e1000_bus_width ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ E1000_SUCCESS ; 
#define  PCIE_LINK_SPEED_2500 129 
#define  PCIE_LINK_SPEED_5000 128 
 int PCIE_LINK_SPEED_MASK ; 
 int /*<<< orphan*/  PCIE_LINK_STATUS ; 
 int PCIE_LINK_WIDTH_MASK ; 
 int PCIE_LINK_WIDTH_SHIFT ; 
 void* e1000_bus_speed_2500 ; 
 void* e1000_bus_speed_5000 ; 
 void* e1000_bus_speed_unknown ; 
 int /*<<< orphan*/  e1000_bus_type_pci_express ; 
 int e1000_bus_width_unknown ; 
 scalar_t__ e1000_read_pcie_cap_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

s32 e1000_get_bus_info_pcie_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	struct e1000_bus_info *bus = &hw->bus;
	s32 ret_val;
	u16 pcie_link_status;

	DEBUGFUNC("e1000_get_bus_info_pcie_generic");

	bus->type = e1000_bus_type_pci_express;

	ret_val = e1000_read_pcie_cap_reg(hw, PCIE_LINK_STATUS,
					  &pcie_link_status);
	if (ret_val) {
		bus->width = e1000_bus_width_unknown;
		bus->speed = e1000_bus_speed_unknown;
	} else {
		switch (pcie_link_status & PCIE_LINK_SPEED_MASK) {
		case PCIE_LINK_SPEED_2500:
			bus->speed = e1000_bus_speed_2500;
			break;
		case PCIE_LINK_SPEED_5000:
			bus->speed = e1000_bus_speed_5000;
			break;
		default:
			bus->speed = e1000_bus_speed_unknown;
			break;
		}

		bus->width = (enum e1000_bus_width)((pcie_link_status &
			      PCIE_LINK_WIDTH_MASK) >> PCIE_LINK_WIDTH_SHIFT);
	}

	mac->ops.set_lan_id(hw);

	return E1000_SUCCESS;
}