#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_ERR_SWFW_SYNC ; 
 int IXGBE_GSSR_EEP_SM ; 
 int IXGBE_GSSR_FLASH_SM ; 
 int IXGBE_GSSR_I2C_MASK ; 
 int IXGBE_GSSR_MAC_CSR_SM ; 
 int IXGBE_GSSR_NVM_PHY_MASK ; 
 int IXGBE_GSSR_PHY0_SM ; 
 int IXGBE_GSSR_PHY1_SM ; 
 int IXGBE_GSSR_SW_MNG_SM ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_SWFW_SYNC_BY_MAC (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ixgbe_get_swfw_sync_semaphore (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_mac_X550 ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync_X540 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync_semaphore (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

s32 ixgbe_acquire_swfw_sync_X540(struct ixgbe_hw *hw, u32 mask)
{
	u32 swmask = mask & IXGBE_GSSR_NVM_PHY_MASK;
	u32 fwmask = swmask << 5;
	u32 swi2c_mask = mask & IXGBE_GSSR_I2C_MASK;
	u32 timeout = 200;
	u32 hwmask = 0;
	u32 swfw_sync;
	u32 i;

	DEBUGFUNC("ixgbe_acquire_swfw_sync_X540");

	if (swmask & IXGBE_GSSR_EEP_SM)
		hwmask |= IXGBE_GSSR_FLASH_SM;

	/* SW only mask doesn't have FW bit pair */
	if (mask & IXGBE_GSSR_SW_MNG_SM)
		swmask |= IXGBE_GSSR_SW_MNG_SM;

	swmask |= swi2c_mask;
	fwmask |= swi2c_mask << 2;
	if (hw->mac.type >= ixgbe_mac_X550)
		timeout = 1000;

	for (i = 0; i < timeout; i++) {
		/* SW NVM semaphore bit is used for access to all
		 * SW_FW_SYNC bits (not just NVM)
		 */
		if (ixgbe_get_swfw_sync_semaphore(hw)) {
			DEBUGOUT("Failed to get NVM access and register semaphore, returning IXGBE_ERR_SWFW_SYNC\n");
			return IXGBE_ERR_SWFW_SYNC;
		}

		swfw_sync = IXGBE_READ_REG(hw, IXGBE_SWFW_SYNC_BY_MAC(hw));
		if (!(swfw_sync & (fwmask | swmask | hwmask))) {
			swfw_sync |= swmask;
			IXGBE_WRITE_REG(hw, IXGBE_SWFW_SYNC_BY_MAC(hw),
					swfw_sync);
			ixgbe_release_swfw_sync_semaphore(hw);
			return IXGBE_SUCCESS;
		}
		/* Firmware currently using resource (fwmask), hardware
		 * currently using resource (hwmask), or other software
		 * thread currently using resource (swmask)
		 */
		ixgbe_release_swfw_sync_semaphore(hw);
		msec_delay(5);
	}

	/* If the resource is not released by the FW/HW the SW can assume that
	 * the FW/HW malfunctions. In that case the SW should set the SW bit(s)
	 * of the requested resource(s) while ignoring the corresponding FW/HW
	 * bits in the SW_FW_SYNC register.
	 */
	if (ixgbe_get_swfw_sync_semaphore(hw)) {
		DEBUGOUT("Failed to get NVM sempahore and register semaphore while forcefully ignoring FW sempahore bit(s) and setting SW semaphore bit(s), returning IXGBE_ERR_SWFW_SYNC\n");
		return IXGBE_ERR_SWFW_SYNC;
	}
	swfw_sync = IXGBE_READ_REG(hw, IXGBE_SWFW_SYNC_BY_MAC(hw));
	if (swfw_sync & (fwmask | hwmask)) {
		swfw_sync |= swmask;
		IXGBE_WRITE_REG(hw, IXGBE_SWFW_SYNC_BY_MAC(hw), swfw_sync);
		ixgbe_release_swfw_sync_semaphore(hw);
		msec_delay(5);
		return IXGBE_SUCCESS;
	}
	/* If the resource is not released by other SW the SW can assume that
	 * the other SW malfunctions. In that case the SW should clear all SW
	 * flags that it does not own and then repeat the whole process once
	 * again.
	 */
	if (swfw_sync & swmask) {
		u32 rmask = IXGBE_GSSR_EEP_SM | IXGBE_GSSR_PHY0_SM |
			    IXGBE_GSSR_PHY1_SM | IXGBE_GSSR_MAC_CSR_SM |
			    IXGBE_GSSR_SW_MNG_SM;

		if (swi2c_mask)
			rmask |= IXGBE_GSSR_I2C_MASK;
		ixgbe_release_swfw_sync_X540(hw, rmask);
		ixgbe_release_swfw_sync_semaphore(hw);
		DEBUGOUT("Resource not released by other SW, returning IXGBE_ERR_SWFW_SYNC\n");
		return IXGBE_ERR_SWFW_SYNC;
	}
	ixgbe_release_swfw_sync_semaphore(hw);
	DEBUGOUT("Returning error IXGBE_ERR_SWFW_SYNC\n");

	return IXGBE_ERR_SWFW_SYNC;
}