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
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  I40E_ERR_PHY ; 
 int /*<<< orphan*/  I40E_GLGEN_I2CPARAMS_DATA_OE_N_MASK ; 
 int /*<<< orphan*/  I40E_GLGEN_I2CPARAMS_DATA_OUT_MASK ; 
 int /*<<< orphan*/  I40E_SUCCESS ; 
 int /*<<< orphan*/  IXL_DBG_I2C ; 
 int /*<<< orphan*/  IXL_I2C_REG (struct i40e_hw*) ; 
 scalar_t__ IXL_I2C_T_FALL ; 
 scalar_t__ IXL_I2C_T_RISE ; 
 scalar_t__ IXL_I2C_T_SU_DATA ; 
 int /*<<< orphan*/  i40e_usec_delay (scalar_t__) ; 
 int /*<<< orphan*/  ixl_dbg (struct ixl_pf*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int ixl_get_i2c_data (struct ixl_pf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32
ixl_set_i2c_data(struct ixl_pf *pf, u32 *i2cctl, bool data)
{
	struct i40e_hw *hw = &pf->hw;
	s32 status = I40E_SUCCESS;

	DEBUGFUNC("ixl_set_i2c_data");

	if (data)
		*i2cctl |= I40E_GLGEN_I2CPARAMS_DATA_OUT_MASK;
	else
		*i2cctl &= ~(I40E_GLGEN_I2CPARAMS_DATA_OUT_MASK);
	*i2cctl &= ~(I40E_GLGEN_I2CPARAMS_DATA_OE_N_MASK);

	wr32(hw, IXL_I2C_REG(hw), *i2cctl);
	ixl_flush(hw);

	/* Data rise/fall (1000ns/300ns) and set-up time (250ns) */
	i40e_usec_delay(IXL_I2C_T_RISE + IXL_I2C_T_FALL + IXL_I2C_T_SU_DATA);

	/* Verify data was set correctly */
	*i2cctl = rd32(hw, IXL_I2C_REG(hw));
	if (data != ixl_get_i2c_data(pf, i2cctl)) {
		status = I40E_ERR_PHY;
		ixl_dbg(pf, IXL_DBG_I2C, "Error - I2C data was not set to %X.\n", data);
	}

	return status;
}