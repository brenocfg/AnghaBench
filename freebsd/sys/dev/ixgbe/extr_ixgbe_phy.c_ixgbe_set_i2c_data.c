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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IXGBE_ERROR_INVALID_STATE ; 
 int /*<<< orphan*/  IXGBE_ERR_I2C ; 
 int /*<<< orphan*/  IXGBE_I2CCTL_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_I2C_DATA_OE_N_EN_BY_MAC (struct ixgbe_hw*) ; 
 int IXGBE_I2C_DATA_OUT_BY_MAC (struct ixgbe_hw*) ; 
 scalar_t__ IXGBE_I2C_T_FALL ; 
 scalar_t__ IXGBE_I2C_T_RISE ; 
 scalar_t__ IXGBE_I2C_T_SU_DATA ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int ixgbe_get_i2c_data (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  usec_delay (scalar_t__) ; 

__attribute__((used)) static s32 ixgbe_set_i2c_data(struct ixgbe_hw *hw, u32 *i2cctl, bool data)
{
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN_BY_MAC(hw);
	s32 status = IXGBE_SUCCESS;

	DEBUGFUNC("ixgbe_set_i2c_data");

	if (data)
		*i2cctl |= IXGBE_I2C_DATA_OUT_BY_MAC(hw);
	else
		*i2cctl &= ~(IXGBE_I2C_DATA_OUT_BY_MAC(hw));
	*i2cctl &= ~data_oe_bit;

	IXGBE_WRITE_REG(hw, IXGBE_I2CCTL_BY_MAC(hw), *i2cctl);
	IXGBE_WRITE_FLUSH(hw);

	/* Data rise/fall (1000ns/300ns) and set-up time (250ns) */
	usec_delay(IXGBE_I2C_T_RISE + IXGBE_I2C_T_FALL + IXGBE_I2C_T_SU_DATA);

	if (!data)	/* Can't verify data in this case */
		return IXGBE_SUCCESS;
	if (data_oe_bit) {
		*i2cctl |= data_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL_BY_MAC(hw), *i2cctl);
		IXGBE_WRITE_FLUSH(hw);
	}

	/* Verify data was set correctly */
	*i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL_BY_MAC(hw));
	if (data != ixgbe_get_i2c_data(hw, i2cctl)) {
		status = IXGBE_ERR_I2C;
		ERROR_REPORT2(IXGBE_ERROR_INVALID_STATE,
			     "Error - I2C data was not set to %X.\n",
			     data);
	}

	return status;
}