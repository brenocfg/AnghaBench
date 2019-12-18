#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,scalar_t__) ;int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,scalar_t__) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ phy_semaphore_mask; } ;
struct ixgbe_hw {TYPE_3__ mac; TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ IXGBE_ERR_SWFW_SYNC ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_clock_out_i2c_byte (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_get_i2c_ack (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_i2c_bus_clear (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_i2c_start (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_i2c_stop (struct ixgbe_hw*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,scalar_t__) ; 

__attribute__((used)) static s32 ixgbe_write_i2c_byte_generic_int(struct ixgbe_hw *hw, u8 byte_offset,
					    u8 dev_addr, u8 data, bool lock)
{
	s32 status;
	u32 max_retry = 1;
	u32 retry = 0;
	u32 swfw_mask = hw->phy.phy_semaphore_mask;

	DEBUGFUNC("ixgbe_write_i2c_byte_generic");

	if (lock && hw->mac.ops.acquire_swfw_sync(hw, swfw_mask) !=
	    IXGBE_SUCCESS)
		return IXGBE_ERR_SWFW_SYNC;

	do {
		ixgbe_i2c_start(hw);

		status = ixgbe_clock_out_i2c_byte(hw, dev_addr);
		if (status != IXGBE_SUCCESS)
			goto fail;

		status = ixgbe_get_i2c_ack(hw);
		if (status != IXGBE_SUCCESS)
			goto fail;

		status = ixgbe_clock_out_i2c_byte(hw, byte_offset);
		if (status != IXGBE_SUCCESS)
			goto fail;

		status = ixgbe_get_i2c_ack(hw);
		if (status != IXGBE_SUCCESS)
			goto fail;

		status = ixgbe_clock_out_i2c_byte(hw, data);
		if (status != IXGBE_SUCCESS)
			goto fail;

		status = ixgbe_get_i2c_ack(hw);
		if (status != IXGBE_SUCCESS)
			goto fail;

		ixgbe_i2c_stop(hw);
		if (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		return IXGBE_SUCCESS;

fail:
		ixgbe_i2c_bus_clear(hw);
		retry++;
		if (retry < max_retry)
			DEBUGOUT("I2C byte write error - Retrying.\n");
		else
			DEBUGOUT("I2C byte write error.\n");
	} while (retry < max_retry);

	if (lock)
		hw->mac.ops.release_swfw_sync(hw, swfw_mask);

	return status;
}