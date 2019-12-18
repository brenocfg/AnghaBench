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
struct e1000_hw {TYPE_1__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_GCR ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int PCIE_NO_SNOOP_ALL ; 
 scalar_t__ e1000_bus_type_pci_express ; 

void e1000_set_pcie_no_snoop_generic(struct e1000_hw *hw, u32 no_snoop)
{
	u32 gcr;

	DEBUGFUNC("e1000_set_pcie_no_snoop_generic");

	if (hw->bus.type != e1000_bus_type_pci_express)
		return;

	if (no_snoop) {
		gcr = E1000_READ_REG(hw, E1000_GCR);
		gcr &= ~(PCIE_NO_SNOOP_ALL);
		gcr |= no_snoop;
		E1000_WRITE_REG(hw, E1000_GCR, gcr);
	}
}