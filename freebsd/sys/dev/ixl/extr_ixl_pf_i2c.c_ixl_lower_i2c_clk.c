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

/* Variables and functions */
 int /*<<< orphan*/  I40E_GLGEN_I2CPARAMS_CLK_MASK ; 
 int /*<<< orphan*/  I40E_GLGEN_I2CPARAMS_CLK_OE_N_MASK ; 
 int /*<<< orphan*/  IXL_I2C_REG (struct i40e_hw*) ; 
 int /*<<< orphan*/  IXL_I2C_T_FALL ; 
 int /*<<< orphan*/  i40e_usec_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_lower_i2c_clk(struct ixl_pf *pf, u32 *i2cctl)
{
	struct i40e_hw *hw = &pf->hw;

	*i2cctl &= ~(I40E_GLGEN_I2CPARAMS_CLK_MASK);
	*i2cctl &= ~(I40E_GLGEN_I2CPARAMS_CLK_OE_N_MASK);

	wr32(hw, IXL_I2C_REG(hw), *i2cctl);
	ixl_flush(hw);

	/* SCL fall time (300ns) */
	i40e_usec_delay(IXL_I2C_T_FALL);
}