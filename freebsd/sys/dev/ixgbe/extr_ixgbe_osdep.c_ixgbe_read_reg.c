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
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_hw {scalar_t__ back; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem_bus_space_handle; int /*<<< orphan*/  mem_bus_space_tag; } ;
struct adapter {TYPE_1__ osdep; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline u32
ixgbe_read_reg(struct ixgbe_hw *hw, u32 reg)
{
	return bus_space_read_4(((struct adapter *)hw->back)->osdep.mem_bus_space_tag,
	    ((struct adapter *)hw->back)->osdep.mem_bus_space_handle, reg);
}