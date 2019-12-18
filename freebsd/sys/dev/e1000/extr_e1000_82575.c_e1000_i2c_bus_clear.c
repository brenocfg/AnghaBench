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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_I2CPARAMS ; 
 int /*<<< orphan*/  E1000_I2C_T_HIGH ; 
 int /*<<< orphan*/  E1000_I2C_T_LOW ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_i2c_start (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_i2c_stop (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_lower_i2c_clk (struct e1000_hw*,int*) ; 
 int /*<<< orphan*/  e1000_raise_i2c_clk (struct e1000_hw*,int*) ; 
 int /*<<< orphan*/  e1000_set_i2c_data (struct e1000_hw*,int*,int) ; 
 int /*<<< orphan*/  usec_delay (int /*<<< orphan*/ ) ; 

void e1000_i2c_bus_clear(struct e1000_hw *hw)
{
	u32 i2cctl = E1000_READ_REG(hw, E1000_I2CPARAMS);
	u32 i;

	DEBUGFUNC("e1000_i2c_bus_clear");

	e1000_i2c_start(hw);

	e1000_set_i2c_data(hw, &i2cctl, 1);

	for (i = 0; i < 9; i++) {
		e1000_raise_i2c_clk(hw, &i2cctl);

		/* Min high period of clock is 4us */
		usec_delay(E1000_I2C_T_HIGH);

		e1000_lower_i2c_clk(hw, &i2cctl);

		/* Min low period of clock is 4.7us*/
		usec_delay(E1000_I2C_T_LOW);
	}

	e1000_i2c_start(hw);

	/* Put the i2c bus back to default state */
	e1000_i2c_stop(hw);
}