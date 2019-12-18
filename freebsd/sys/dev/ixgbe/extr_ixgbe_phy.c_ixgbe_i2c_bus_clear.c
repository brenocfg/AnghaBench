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
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_I2CCTL_BY_MAC (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_I2C_T_HIGH ; 
 int /*<<< orphan*/  IXGBE_I2C_T_LOW ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_i2c_start (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_i2c_stop (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_lower_i2c_clk (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  ixgbe_raise_i2c_clk (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  ixgbe_set_i2c_data (struct ixgbe_hw*,int*,int) ; 
 int /*<<< orphan*/  usec_delay (int /*<<< orphan*/ ) ; 

void ixgbe_i2c_bus_clear(struct ixgbe_hw *hw)
{
	u32 i2cctl;
	u32 i;

	DEBUGFUNC("ixgbe_i2c_bus_clear");

	ixgbe_i2c_start(hw);
	i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL_BY_MAC(hw));

	ixgbe_set_i2c_data(hw, &i2cctl, 1);

	for (i = 0; i < 9; i++) {
		ixgbe_raise_i2c_clk(hw, &i2cctl);

		/* Min high period of clock is 4us */
		usec_delay(IXGBE_I2C_T_HIGH);

		ixgbe_lower_i2c_clk(hw, &i2cctl);

		/* Min low period of clock is 4.7us*/
		usec_delay(IXGBE_I2C_T_LOW);
	}

	ixgbe_i2c_start(hw);

	/* Put the i2c bus back to default state */
	ixgbe_i2c_stop(hw);
}