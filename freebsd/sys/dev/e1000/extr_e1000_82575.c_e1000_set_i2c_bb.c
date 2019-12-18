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
typedef  int /*<<< orphan*/  u32 ;
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int /*<<< orphan*/  E1000_CTRL_I2C_ENA ; 
 int /*<<< orphan*/  E1000_I2CBB_EN ; 
 int /*<<< orphan*/  E1000_I2CPARAMS ; 
 int /*<<< orphan*/  E1000_I2C_CLK_OE_N ; 
 int /*<<< orphan*/  E1000_I2C_DATA_OE_N ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 e1000_set_i2c_bb(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;
	u32 ctrl_ext, i2cparams;

	DEBUGFUNC("e1000_set_i2c_bb");

	ctrl_ext = E1000_READ_REG(hw, E1000_CTRL_EXT);
	ctrl_ext |= E1000_CTRL_I2C_ENA;
	E1000_WRITE_REG(hw, E1000_CTRL_EXT, ctrl_ext);
	E1000_WRITE_FLUSH(hw);

	i2cparams = E1000_READ_REG(hw, E1000_I2CPARAMS);
	i2cparams |= E1000_I2CBB_EN;
	i2cparams |= E1000_I2C_DATA_OE_N;
	i2cparams |= E1000_I2C_CLK_OE_N;
	E1000_WRITE_REG(hw, E1000_I2CPARAMS, i2cparams);
	E1000_WRITE_FLUSH(hw);

	return ret_val;
}