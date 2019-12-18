#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* set_lan_id ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  width; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_bus_speed_unknown ; 
 int /*<<< orphan*/  ixgbe_bus_width_unknown ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 

s32 ixgbe_get_bus_info_X550em(struct ixgbe_hw *hw)
{

	DEBUGFUNC("ixgbe_get_bus_info_x550em");

	hw->bus.width = ixgbe_bus_width_unknown;
	hw->bus.speed = ixgbe_bus_speed_unknown;

	hw->mac.ops.set_lan_id(hw);

	return IXGBE_SUCCESS;
}