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
 int /*<<< orphan*/  E1000_I2CPARAMS ; 
 int /*<<< orphan*/  E1000_I2C_T_HIGH ; 
 int /*<<< orphan*/  E1000_I2C_T_LOW ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int e1000_get_i2c_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_lower_i2c_clk (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_raise_i2c_clk (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usec_delay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_clock_in_i2c_bit(struct e1000_hw *hw, bool *data)
{
	u32 i2cctl = E1000_READ_REG(hw, E1000_I2CPARAMS);

	DEBUGFUNC("e1000_clock_in_i2c_bit");

	e1000_raise_i2c_clk(hw, &i2cctl);

	/* Minimum high period of clock is 4us */
	usec_delay(E1000_I2C_T_HIGH);

	i2cctl = E1000_READ_REG(hw, E1000_I2CPARAMS);
	*data = e1000_get_i2c_data(&i2cctl);

	e1000_lower_i2c_clk(hw, &i2cctl);

	/* Minimum low period of clock is 4.7 us */
	usec_delay(E1000_I2C_T_LOW);

	return E1000_SUCCESS;
}