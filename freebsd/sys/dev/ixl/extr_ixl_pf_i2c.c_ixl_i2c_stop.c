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
 int /*<<< orphan*/  IXL_I2C_T_BUF ; 
 int /*<<< orphan*/  IXL_I2C_T_SU_STO ; 
 int /*<<< orphan*/  i40e_usec_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_raise_i2c_clk (struct ixl_pf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_set_i2c_data (struct ixl_pf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_i2c_stop(struct ixl_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u32 i2cctl = rd32(hw, IXL_I2C_REG(hw));

	DEBUGFUNC("ixl_i2c_stop");

	/* Stop condition must begin with data low and clock high */
	ixl_set_i2c_data(pf, &i2cctl, 0);
	ixl_raise_i2c_clk(pf, &i2cctl);

	/* Setup time for stop condition (4us) */
	i40e_usec_delay(IXL_I2C_T_SU_STO);

	ixl_set_i2c_data(pf, &i2cctl, 1);

	/* bus free time between stop and start (4.7us)*/
	i40e_usec_delay(IXL_I2C_T_BUF);
}