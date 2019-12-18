#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ (* acquire_swfw_sync ) (struct e1000_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release_swfw_sync ) (struct e1000_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ E1000_ERR_SWFW_SYNC ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_SWFW_PHY0_SM ; 
 int TRUE ; 
 scalar_t__ e1000_clock_in_i2c_byte (struct e1000_hw*,int*) ; 
 scalar_t__ e1000_clock_out_i2c_bit (struct e1000_hw*,int) ; 
 scalar_t__ e1000_clock_out_i2c_byte (struct e1000_hw*,int) ; 
 scalar_t__ e1000_get_i2c_ack (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_i2c_bus_clear (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_i2c_start (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_i2c_stop (struct e1000_hw*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int /*<<< orphan*/ ) ; 

s32 e1000_read_i2c_byte_generic(struct e1000_hw *hw, u8 byte_offset,
				u8 dev_addr, u8 *data)
{
	s32 status = E1000_SUCCESS;
	u32 max_retry = 10;
	u32 retry = 1;
	u16 swfw_mask = 0;

	bool nack = TRUE;

	DEBUGFUNC("e1000_read_i2c_byte_generic");

	swfw_mask = E1000_SWFW_PHY0_SM;

	do {
		if (hw->mac.ops.acquire_swfw_sync(hw, swfw_mask)
		    != E1000_SUCCESS) {
			status = E1000_ERR_SWFW_SYNC;
			goto read_byte_out;
		}

		e1000_i2c_start(hw);

		/* Device Address and write indication */
		status = e1000_clock_out_i2c_byte(hw, dev_addr);
		if (status != E1000_SUCCESS)
			goto fail;

		status = e1000_get_i2c_ack(hw);
		if (status != E1000_SUCCESS)
			goto fail;

		status = e1000_clock_out_i2c_byte(hw, byte_offset);
		if (status != E1000_SUCCESS)
			goto fail;

		status = e1000_get_i2c_ack(hw);
		if (status != E1000_SUCCESS)
			goto fail;

		e1000_i2c_start(hw);

		/* Device Address and read indication */
		status = e1000_clock_out_i2c_byte(hw, (dev_addr | 0x1));
		if (status != E1000_SUCCESS)
			goto fail;

		status = e1000_get_i2c_ack(hw);
		if (status != E1000_SUCCESS)
			goto fail;

		status = e1000_clock_in_i2c_byte(hw, data);
		if (status != E1000_SUCCESS)
			goto fail;

		status = e1000_clock_out_i2c_bit(hw, nack);
		if (status != E1000_SUCCESS)
			goto fail;

		e1000_i2c_stop(hw);
		break;

fail:
		hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		msec_delay(100);
		e1000_i2c_bus_clear(hw);
		retry++;
		if (retry < max_retry)
			DEBUGOUT("I2C byte read error - Retrying.\n");
		else
			DEBUGOUT("I2C byte read error.\n");

	} while (retry < max_retry);

	hw->mac.ops.release_swfw_sync(hw, swfw_mask);

read_byte_out:

	return status;
}