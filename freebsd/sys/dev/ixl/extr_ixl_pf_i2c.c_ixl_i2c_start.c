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
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXL_I2C_REG (struct i40e_hw*) ; 
 int /*<<< orphan*/  IXL_I2C_T_HD_STA ; 
 int /*<<< orphan*/  IXL_I2C_T_LOW ; 
 int /*<<< orphan*/  IXL_I2C_T_SU_STA ; 
 int /*<<< orphan*/  i40e_usec_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_lower_i2c_clk (struct ixl_pf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_raise_i2c_clk (struct ixl_pf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_set_i2c_data (struct ixl_pf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_i2c_start(struct ixl_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u32 i2cctl = rd32(hw, IXL_I2C_REG(hw));

	DEBUGFUNC("ixl_i2c_start");

	/* Start condition must begin with data and clock high */
	ixl_set_i2c_data(pf, &i2cctl, 1);
	ixl_raise_i2c_clk(pf, &i2cctl);

	/* Setup time for start condition (4.7us) */
	i40e_usec_delay(IXL_I2C_T_SU_STA);

	ixl_set_i2c_data(pf, &i2cctl, 0);

	/* Hold time for start condition (4us) */
	i40e_usec_delay(IXL_I2C_T_HD_STA);

	ixl_lower_i2c_clk(pf, &i2cctl);

	/* Minimum low period of clock is 4.7 us */
	i40e_usec_delay(IXL_I2C_T_LOW);

}