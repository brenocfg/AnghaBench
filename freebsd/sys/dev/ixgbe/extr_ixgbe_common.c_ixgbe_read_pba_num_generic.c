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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* read ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ IXGBE_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  IXGBE_PBANUM0_PTR ; 
 int /*<<< orphan*/  IXGBE_PBANUM1_PTR ; 
 int IXGBE_PBANUM_PTR_GUARD ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 

s32 ixgbe_read_pba_num_generic(struct ixgbe_hw *hw, u32 *pba_num)
{
	s32 ret_val;
	u16 data;

	DEBUGFUNC("ixgbe_read_pba_num_generic");

	ret_val = hw->eeprom.ops.read(hw, IXGBE_PBANUM0_PTR, &data);
	if (ret_val) {
		DEBUGOUT("NVM Read Error\n");
		return ret_val;
	} else if (data == IXGBE_PBANUM_PTR_GUARD) {
		DEBUGOUT("NVM Not supported\n");
		return IXGBE_NOT_IMPLEMENTED;
	}
	*pba_num = (u32)(data << 16);

	ret_val = hw->eeprom.ops.read(hw, IXGBE_PBANUM1_PTR, &data);
	if (ret_val) {
		DEBUGOUT("NVM Read Error\n");
		return ret_val;
	}
	*pba_num |= data;

	return IXGBE_SUCCESS;
}