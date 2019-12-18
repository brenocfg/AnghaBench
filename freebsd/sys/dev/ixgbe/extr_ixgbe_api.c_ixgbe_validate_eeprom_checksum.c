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
struct TYPE_3__ {int /*<<< orphan*/  validate_checksum; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ixgbe_call_func (struct ixgbe_hw*,int /*<<< orphan*/ ,struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

s32 ixgbe_validate_eeprom_checksum(struct ixgbe_hw *hw, u16 *checksum_val)
{
	return ixgbe_call_func(hw, hw->eeprom.ops.validate_checksum,
			       (hw, checksum_val), IXGBE_NOT_IMPLEMENTED);
}