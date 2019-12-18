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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 scalar_t__ E1000_ERR_I2C ; 
 int /*<<< orphan*/  E1000_I2CPARAMS ; 
 int /*<<< orphan*/  E1000_I2C_T_HIGH ; 
 int /*<<< orphan*/  E1000_I2C_T_LOW ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_lower_i2c_clk (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_raise_i2c_clk (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_set_i2c_data (struct e1000_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usec_delay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_clock_out_i2c_bit(struct e1000_hw *hw, bool data)
{
	s32 status;
	u32 i2cctl = E1000_READ_REG(hw, E1000_I2CPARAMS);

	DEBUGFUNC("e1000_clock_out_i2c_bit");

	status = e1000_set_i2c_data(hw, &i2cctl, data);
	if (status == E1000_SUCCESS) {
		e1000_raise_i2c_clk(hw, &i2cctl);

		/* Minimum high period of clock is 4us */
		usec_delay(E1000_I2C_T_HIGH);

		e1000_lower_i2c_clk(hw, &i2cctl);

		/* Minimum low period of clock is 4.7 us.
		 * This also takes care of the data hold time.
		 */
		usec_delay(E1000_I2C_T_LOW);
	} else {
		status = E1000_ERR_I2C;
		DEBUGOUT1("I2C data was not set to %X\n", data);
	}

	return status;
}