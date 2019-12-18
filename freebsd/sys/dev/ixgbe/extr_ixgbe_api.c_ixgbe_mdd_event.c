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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* mdd_event ) (struct ixgbe_hw*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 

void ixgbe_mdd_event(struct ixgbe_hw *hw, u32 *vf_bitmap)
{
	if (hw->mac.ops.mdd_event)
		hw->mac.ops.mdd_event(hw, vf_bitmap);
}