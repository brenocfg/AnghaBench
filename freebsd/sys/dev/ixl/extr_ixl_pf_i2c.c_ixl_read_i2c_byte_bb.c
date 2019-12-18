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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ I40E_GLGEN_I2CPARAMS_I2CBB_EN_MASK ; 
 int /*<<< orphan*/  I40E_SUCCESS ; 
 int /*<<< orphan*/  IXL_DBG_I2C ; 
 int /*<<< orphan*/  IXL_I2C_REG (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_msec_delay (int) ; 
 int /*<<< orphan*/  ixl_clock_in_i2c_byte (struct ixl_pf*,int*) ; 
 int /*<<< orphan*/  ixl_clock_out_i2c_bit (struct ixl_pf*,int) ; 
 int /*<<< orphan*/  ixl_clock_out_i2c_byte (struct ixl_pf*,int) ; 
 int /*<<< orphan*/  ixl_dbg (struct ixl_pf*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_get_i2c_ack (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_i2c_bus_clear (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_i2c_start (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_i2c_stop (struct ixl_pf*) ; 
 scalar_t__ rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

s32
ixl_read_i2c_byte_bb(struct ixl_pf *pf, u8 byte_offset,
		  u8 dev_addr, u8 *data)
{
	struct i40e_hw *hw = &pf->hw;
	u32 max_retry = 10;
	u32 retry = 0;
	bool nack = 1;
	s32 status;
	*data = 0;

	u32 i2cctl = rd32(hw, IXL_I2C_REG(hw));
	i2cctl |= I40E_GLGEN_I2CPARAMS_I2CBB_EN_MASK;
	wr32(hw, IXL_I2C_REG(hw), i2cctl);
	ixl_flush(hw);

	do {
		ixl_i2c_start(pf);

		/* Device Address and write indication */
		status = ixl_clock_out_i2c_byte(pf, dev_addr);
		if (status != I40E_SUCCESS) {
			ixl_dbg(pf, IXL_DBG_I2C, "dev_addr clock out error\n");
			goto fail;
		}

		status = ixl_get_i2c_ack(pf);
		if (status != I40E_SUCCESS) {
			ixl_dbg(pf, IXL_DBG_I2C, "dev_addr i2c ack error\n");
			goto fail;
		}

		status = ixl_clock_out_i2c_byte(pf, byte_offset);
		if (status != I40E_SUCCESS) {
			ixl_dbg(pf, IXL_DBG_I2C, "byte_offset clock out error\n");
			goto fail;
		}

		status = ixl_get_i2c_ack(pf);
		if (status != I40E_SUCCESS) {
			ixl_dbg(pf, IXL_DBG_I2C, "byte_offset i2c ack error\n");
			goto fail;
		}

		ixl_i2c_start(pf);

		/* Device Address and read indication */
		status = ixl_clock_out_i2c_byte(pf, (dev_addr | 0x1));
		if (status != I40E_SUCCESS)
			goto fail;

		status = ixl_get_i2c_ack(pf);
		if (status != I40E_SUCCESS)
			goto fail;

		status = ixl_clock_in_i2c_byte(pf, data);
		if (status != I40E_SUCCESS)
			goto fail;

		status = ixl_clock_out_i2c_bit(pf, nack);
		if (status != I40E_SUCCESS)
			goto fail;

		ixl_i2c_stop(pf);
		status = I40E_SUCCESS;
		goto done;

fail:
		ixl_i2c_bus_clear(pf);
		i40e_msec_delay(100);
		retry++;
		if (retry < max_retry)
			ixl_dbg(pf, IXL_DBG_I2C, "I2C byte read error - Retrying\n");
		else
			ixl_dbg(pf, IXL_DBG_I2C, "I2C byte read error\n");

	} while (retry < max_retry);
done:
	i2cctl = rd32(hw, IXL_I2C_REG(hw));
	i2cctl &= ~I40E_GLGEN_I2CPARAMS_I2CBB_EN_MASK;
	wr32(hw, IXL_I2C_REG(hw), i2cctl);
	ixl_flush(hw);

	return status;
}