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
struct TYPE_2__ {int /*<<< orphan*/  (* set_lan_id ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {TYPE_1__ ops; } ;
struct e1000_bus_info {scalar_t__ type; int /*<<< orphan*/  width; void* speed; } ;
struct e1000_hw {struct e1000_bus_info bus; struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_BUS64 ; 
 int E1000_STATUS_PCI66 ; 
 int E1000_STATUS_PCIX_MODE ; 
 int E1000_STATUS_PCIX_SPEED ; 
#define  E1000_STATUS_PCIX_SPEED_100 130 
#define  E1000_STATUS_PCIX_SPEED_133 129 
#define  E1000_STATUS_PCIX_SPEED_66 128 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 void* e1000_bus_speed_100 ; 
 void* e1000_bus_speed_133 ; 
 void* e1000_bus_speed_33 ; 
 void* e1000_bus_speed_66 ; 
 void* e1000_bus_speed_reserved ; 
 scalar_t__ e1000_bus_type_pci ; 
 scalar_t__ e1000_bus_type_pcix ; 
 int /*<<< orphan*/  e1000_bus_width_32 ; 
 int /*<<< orphan*/  e1000_bus_width_64 ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

s32 e1000_get_bus_info_pci_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	struct e1000_bus_info *bus = &hw->bus;
	u32 status = E1000_READ_REG(hw, E1000_STATUS);
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_get_bus_info_pci_generic");

	/* PCI or PCI-X? */
	bus->type = (status & E1000_STATUS_PCIX_MODE)
			? e1000_bus_type_pcix
			: e1000_bus_type_pci;

	/* Bus speed */
	if (bus->type == e1000_bus_type_pci) {
		bus->speed = (status & E1000_STATUS_PCI66)
			     ? e1000_bus_speed_66
			     : e1000_bus_speed_33;
	} else {
		switch (status & E1000_STATUS_PCIX_SPEED) {
		case E1000_STATUS_PCIX_SPEED_66:
			bus->speed = e1000_bus_speed_66;
			break;
		case E1000_STATUS_PCIX_SPEED_100:
			bus->speed = e1000_bus_speed_100;
			break;
		case E1000_STATUS_PCIX_SPEED_133:
			bus->speed = e1000_bus_speed_133;
			break;
		default:
			bus->speed = e1000_bus_speed_reserved;
			break;
		}
	}

	/* Bus width */
	bus->width = (status & E1000_STATUS_BUS64)
		     ? e1000_bus_width_64
		     : e1000_bus_width_32;

	/* Which PCI(-X) function? */
	mac->ops.set_lan_id(hw);

	return ret_val;
}