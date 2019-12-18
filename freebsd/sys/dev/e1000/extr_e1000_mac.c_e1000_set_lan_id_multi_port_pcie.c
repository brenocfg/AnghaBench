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
typedef  int u32 ;
struct e1000_bus_info {int func; } ;
struct e1000_hw {struct e1000_bus_info bus; } ;

/* Variables and functions */
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_FUNC_MASK ; 
 int E1000_STATUS_FUNC_SHIFT ; 

__attribute__((used)) static void e1000_set_lan_id_multi_port_pcie(struct e1000_hw *hw)
{
	struct e1000_bus_info *bus = &hw->bus;
	u32 reg;

	/* The status register reports the correct function number
	 * for the device regardless of function swap state.
	 */
	reg = E1000_READ_REG(hw, E1000_STATUS);
	bus->func = (reg & E1000_STATUS_FUNC_MASK) >> E1000_STATUS_FUNC_SHIFT;
}