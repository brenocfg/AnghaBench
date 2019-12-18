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
struct TYPE_3__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* check_reset_block ) (struct e1000_hw*) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  HV_OEM_BITS ; 
 int /*<<< orphan*/  HV_OEM_BITS_LPLU ; 
 int /*<<< orphan*/  HV_OEM_BITS_RESTART_AN ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_set_lplu_state_pchlan(struct e1000_hw *hw, bool active)
{
	s32 ret_val;
	u16 oem_reg;

	DEBUGFUNC("e1000_set_lplu_state_pchlan");
	ret_val = hw->phy.ops.read_reg(hw, HV_OEM_BITS, &oem_reg);
	if (ret_val)
		return ret_val;

	if (active)
		oem_reg |= HV_OEM_BITS_LPLU;
	else
		oem_reg &= ~HV_OEM_BITS_LPLU;

	if (!hw->phy.ops.check_reset_block(hw))
		oem_reg |= HV_OEM_BITS_RESTART_AN;

	return hw->phy.ops.write_reg(hw, HV_OEM_BITS, oem_reg);
}