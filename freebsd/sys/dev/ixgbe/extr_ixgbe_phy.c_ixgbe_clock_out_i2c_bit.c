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
struct ixgbe_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IXGBE_ERROR_INVALID_STATE ; 
 scalar_t__ IXGBE_ERR_I2C ; 
 int /*<<< orphan*/  IXGBE_I2CCTL_BY_MAC (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_I2C_T_HIGH ; 
 int /*<<< orphan*/  IXGBE_I2C_T_LOW ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_lower_i2c_clk (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_raise_i2c_clk (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ ixgbe_set_i2c_data (struct ixgbe_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usec_delay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_clock_out_i2c_bit(struct ixgbe_hw *hw, bool data)
{
	s32 status;
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL_BY_MAC(hw));

	DEBUGFUNC("ixgbe_clock_out_i2c_bit");

	status = ixgbe_set_i2c_data(hw, &i2cctl, data);
	if (status == IXGBE_SUCCESS) {
		ixgbe_raise_i2c_clk(hw, &i2cctl);

		/* Minimum high period of clock is 4us */
		usec_delay(IXGBE_I2C_T_HIGH);

		ixgbe_lower_i2c_clk(hw, &i2cctl);

		/* Minimum low period of clock is 4.7 us.
		 * This also takes care of the data hold time.
		 */
		usec_delay(IXGBE_I2C_T_LOW);
	} else {
		status = IXGBE_ERR_I2C;
		ERROR_REPORT2(IXGBE_ERROR_INVALID_STATE,
			     "I2C data was not set to %X\n", data);
	}

	return status;
}