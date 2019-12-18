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
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  I40E_GLGEN_I2CPARAMS_DATA_OE_N_MASK ; 
 int /*<<< orphan*/  I40E_SUCCESS ; 
 int /*<<< orphan*/  IXL_I2C_REG (struct i40e_hw*) ; 
 int /*<<< orphan*/  IXL_I2C_T_HIGH ; 
 int /*<<< orphan*/  IXL_I2C_T_LOW ; 
 int /*<<< orphan*/  i40e_usec_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int ixl_get_i2c_data (struct ixl_pf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_lower_i2c_clk (struct ixl_pf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_raise_i2c_clk (struct ixl_pf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32
ixl_clock_in_i2c_bit(struct ixl_pf *pf, bool *data)
{
	struct i40e_hw *hw = &pf->hw;
	u32 i2cctl = rd32(hw, IXL_I2C_REG(hw));

	DEBUGFUNC("ixl_clock_in_i2c_bit");

	ixl_raise_i2c_clk(pf, &i2cctl);

	/* Minimum high period of clock is 4us */
	i40e_usec_delay(IXL_I2C_T_HIGH);

	i2cctl = rd32(hw, IXL_I2C_REG(hw));
	i2cctl |= I40E_GLGEN_I2CPARAMS_DATA_OE_N_MASK;
	wr32(hw, IXL_I2C_REG(hw), i2cctl);
	ixl_flush(hw);

	i2cctl = rd32(hw, IXL_I2C_REG(hw));
	*data = ixl_get_i2c_data(pf, &i2cctl);

	ixl_lower_i2c_clk(pf, &i2cctl);

	/* Minimum low period of clock is 4.7 us */
	i40e_usec_delay(IXL_I2C_T_LOW);

	return I40E_SUCCESS;
}