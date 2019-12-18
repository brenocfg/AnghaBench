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
 int IXGBE_I2C_CLK_IN_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_I2C_CLK_OE_N_EN_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_I2C_CLK_OUT_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_I2C_CLOCK_STRETCHING_TIMEOUT ; 
 int /*<<< orphan*/  IXGBE_I2C_T_RISE ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usec_delay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_raise_i2c_clk(struct ixgbe_hw *hw, u32 *i2cctl)
{
	u32 clk_oe_bit = IXGBE_I2C_CLK_OE_N_EN_BY_MAC(hw);
	u32 i = 0;
	u32 timeout = IXGBE_I2C_CLOCK_STRETCHING_TIMEOUT;
	u32 i2cctl_r = 0;

	DEBUGFUNC("ixgbe_raise_i2c_clk");

	if (clk_oe_bit) {
		*i2cctl |= clk_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL_BY_MAC(hw), *i2cctl);
	}

	for (i = 0; i < timeout; i++) {
		*i2cctl |= IXGBE_I2C_CLK_OUT_BY_MAC(hw);

		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL_BY_MAC(hw), *i2cctl);
		IXGBE_WRITE_FLUSH(hw);
		/* SCL rise time (1000ns) */
		usec_delay(IXGBE_I2C_T_RISE);

		i2cctl_r = IXGBE_READ_REG(hw, IXGBE_I2CCTL_BY_MAC(hw));
		if (i2cctl_r & IXGBE_I2C_CLK_IN_BY_MAC(hw))
			break;
	}
}