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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_SPD_BYPS ; 
 int E1000_CTRL_FRCSPD ; 
 int E1000_CTRL_SPD_100 ; 
 int E1000_CTRL_SPD_1000 ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_K1_CONFIG ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_K1_ENABLE ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_read_kmrn_reg_locked (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_write_kmrn_reg_locked (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 e1000_configure_k1_ich8lan(struct e1000_hw *hw, bool k1_enable)
{
	s32 ret_val;
	u32 ctrl_reg = 0;
	u32 ctrl_ext = 0;
	u32 reg = 0;
	u16 kmrn_reg = 0;

	DEBUGFUNC("e1000_configure_k1_ich8lan");

	ret_val = e1000_read_kmrn_reg_locked(hw, E1000_KMRNCTRLSTA_K1_CONFIG,
					     &kmrn_reg);
	if (ret_val)
		return ret_val;

	if (k1_enable)
		kmrn_reg |= E1000_KMRNCTRLSTA_K1_ENABLE;
	else
		kmrn_reg &= ~E1000_KMRNCTRLSTA_K1_ENABLE;

	ret_val = e1000_write_kmrn_reg_locked(hw, E1000_KMRNCTRLSTA_K1_CONFIG,
					      kmrn_reg);
	if (ret_val)
		return ret_val;

	usec_delay(20);
	ctrl_ext = E1000_READ_REG(hw, E1000_CTRL_EXT);
	ctrl_reg = E1000_READ_REG(hw, E1000_CTRL);

	reg = ctrl_reg & ~(E1000_CTRL_SPD_1000 | E1000_CTRL_SPD_100);
	reg |= E1000_CTRL_FRCSPD;
	E1000_WRITE_REG(hw, E1000_CTRL, reg);

	E1000_WRITE_REG(hw, E1000_CTRL_EXT, ctrl_ext | E1000_CTRL_EXT_SPD_BYPS);
	E1000_WRITE_FLUSH(hw);
	usec_delay(20);
	E1000_WRITE_REG(hw, E1000_CTRL, ctrl_reg);
	E1000_WRITE_REG(hw, E1000_CTRL_EXT, ctrl_ext);
	E1000_WRITE_FLUSH(hw);
	usec_delay(20);

	return E1000_SUCCESS;
}