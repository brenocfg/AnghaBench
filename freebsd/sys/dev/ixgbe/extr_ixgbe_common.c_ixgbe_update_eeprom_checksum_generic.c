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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int (* read ) (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ;int (* calc_checksum ) (struct ixgbe_hw*) ;int (* write ) (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_EEPROM_CHECKSUM ; 
 int stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int stub2 (struct ixgbe_hw*) ; 
 int stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

s32 ixgbe_update_eeprom_checksum_generic(struct ixgbe_hw *hw)
{
	s32 status;
	u16 checksum;

	DEBUGFUNC("ixgbe_update_eeprom_checksum_generic");

	/* Read the first word from the EEPROM. If this times out or fails, do
	 * not continue or we could be in for a very long wait while every
	 * EEPROM read fails
	 */
	status = hw->eeprom.ops.read(hw, 0, &checksum);
	if (status) {
		DEBUGOUT("EEPROM read failed\n");
		return status;
	}

	status = hw->eeprom.ops.calc_checksum(hw);
	if (status < 0)
		return status;

	checksum = (u16)(status & 0xffff);

	status = hw->eeprom.ops.write(hw, IXGBE_EEPROM_CHECKSUM, checksum);

	return status;
}