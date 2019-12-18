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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  get_firmware_version; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_call_func (struct ixgbe_hw*,int /*<<< orphan*/ ,struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

s32 ixgbe_get_phy_firmware_version(struct ixgbe_hw *hw, u16 *firmware_version)
{
	s32 status = IXGBE_SUCCESS;

	status = ixgbe_call_func(hw, hw->phy.ops.get_firmware_version,
				 (hw, firmware_version),
				 IXGBE_NOT_IMPLEMENTED);
	return status;
}