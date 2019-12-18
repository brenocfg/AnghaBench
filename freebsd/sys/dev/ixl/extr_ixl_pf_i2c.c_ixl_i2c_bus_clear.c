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
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXL_I2C_REG (struct i40e_hw*) ; 
 int /*<<< orphan*/  IXL_I2C_T_HIGH ; 
 int /*<<< orphan*/  IXL_I2C_T_LOW ; 
 int /*<<< orphan*/  i40e_usec_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_i2c_start (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_i2c_stop (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_lower_i2c_clk (struct ixl_pf*,int*) ; 
 int /*<<< orphan*/  ixl_raise_i2c_clk (struct ixl_pf*,int*) ; 
 int /*<<< orphan*/  ixl_set_i2c_data (struct ixl_pf*,int*,int) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_i2c_bus_clear(struct ixl_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u32 i2cctl = rd32(hw, IXL_I2C_REG(hw));
	u32 i;

	DEBUGFUNC("ixl_i2c_bus_clear");

	ixl_i2c_start(pf);

	ixl_set_i2c_data(pf, &i2cctl, 1);

	for (i = 0; i < 9; i++) {
		ixl_raise_i2c_clk(pf, &i2cctl);

		/* Min high period of clock is 4us */
		i40e_usec_delay(IXL_I2C_T_HIGH);

		ixl_lower_i2c_clk(pf, &i2cctl);

		/* Min low period of clock is 4.7us*/
		i40e_usec_delay(IXL_I2C_T_LOW);
	}

	ixl_i2c_start(pf);

	/* Put the i2c bus back to default state */
	ixl_i2c_stop(pf);
}