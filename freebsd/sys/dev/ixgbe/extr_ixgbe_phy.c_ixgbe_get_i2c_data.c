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
 int IXGBE_I2C_DATA_IN_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_I2C_DATA_OE_N_EN_BY_MAC (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_I2C_T_FALL ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  usec_delay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ixgbe_get_i2c_data(struct ixgbe_hw *hw, u32 *i2cctl)
{
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN_BY_MAC(hw);
	bool data;
	UNREFERENCED_1PARAMETER(hw);

	DEBUGFUNC("ixgbe_get_i2c_data");

	if (data_oe_bit) {
		*i2cctl |= data_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL_BY_MAC(hw), *i2cctl);
		IXGBE_WRITE_FLUSH(hw);
		usec_delay(IXGBE_I2C_T_FALL);
	}

	if (*i2cctl & IXGBE_I2C_DATA_IN_BY_MAC(hw))
		data = 1;
	else
		data = 0;

	return data;
}