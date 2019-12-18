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
typedef  scalar_t__ u32 ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PHY ; 
 scalar_t__ I40E_GLGEN_I2CPARAMS_DATA_OE_N_MASK ; 
 int /*<<< orphan*/  I40E_SUCCESS ; 
 int /*<<< orphan*/  IXL_DBG_I2C ; 
 int /*<<< orphan*/  IXL_I2C_REG (struct i40e_hw*) ; 
 int IXL_I2C_T_HIGH ; 
 int IXL_I2C_T_LOW ; 
 int /*<<< orphan*/  i40e_usec_delay (int) ; 
 int /*<<< orphan*/  ixl_dbg (struct ixl_pf*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int ixl_get_i2c_data (struct ixl_pf*,scalar_t__*) ; 
 int /*<<< orphan*/  ixl_lower_i2c_clk (struct ixl_pf*,scalar_t__*) ; 
 int /*<<< orphan*/  ixl_raise_i2c_clk (struct ixl_pf*,scalar_t__*) ; 
 scalar_t__ rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static s32
ixl_get_i2c_ack(struct ixl_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	s32 status = I40E_SUCCESS;
	u32 i = 0;
	u32 i2cctl = rd32(hw, IXL_I2C_REG(hw));
	u32 timeout = 10;
	bool ack = 1;

	ixl_raise_i2c_clk(pf, &i2cctl);

	/* Minimum high period of clock is 4us */
	i40e_usec_delay(IXL_I2C_T_HIGH);

	i2cctl = rd32(hw, IXL_I2C_REG(hw));
	i2cctl |= I40E_GLGEN_I2CPARAMS_DATA_OE_N_MASK;
	wr32(hw, IXL_I2C_REG(hw), i2cctl);
	ixl_flush(hw);

	/* Poll for ACK.  Note that ACK in I2C spec is
	 * transition from 1 to 0 */
	for (i = 0; i < timeout; i++) {
		i2cctl = rd32(hw, IXL_I2C_REG(hw));
		ack = ixl_get_i2c_data(pf, &i2cctl);

		i40e_usec_delay(1);
		if (!ack)
			break;
	}

	if (ack) {
		ixl_dbg(pf, IXL_DBG_I2C, "I2C ack was not received.\n");
		status = I40E_ERR_PHY;
	}

	ixl_lower_i2c_clk(pf, &i2cctl);

	/* Minimum low period of clock is 4.7 us */
	i40e_usec_delay(IXL_I2C_T_LOW);

	return status;
}