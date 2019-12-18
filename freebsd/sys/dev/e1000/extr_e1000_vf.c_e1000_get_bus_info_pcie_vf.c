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
struct e1000_bus_info {int /*<<< orphan*/  speed; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_bus_info bus; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  e1000_bus_speed_2500 ; 
 int /*<<< orphan*/  e1000_bus_type_reserved ; 

__attribute__((used)) static s32 e1000_get_bus_info_pcie_vf(struct e1000_hw *hw)
{
	struct e1000_bus_info *bus = &hw->bus;

	DEBUGFUNC("e1000_get_bus_info_pcie_vf");

	/* Do not set type PCI-E because we don't want disable master to run */
	bus->type = e1000_bus_type_reserved;
	bus->speed = e1000_bus_speed_2500;

	return 0;
}