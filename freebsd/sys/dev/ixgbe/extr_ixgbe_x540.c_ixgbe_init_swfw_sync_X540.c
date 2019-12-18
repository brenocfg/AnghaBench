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
 int IXGBE_GSSR_EEP_SM ; 
 int IXGBE_GSSR_I2C_MASK ; 
 int IXGBE_GSSR_MAC_CSR_SM ; 
 int IXGBE_GSSR_PHY0_SM ; 
 int IXGBE_GSSR_PHY1_SM ; 
 int IXGBE_GSSR_SW_MNG_SM ; 
 int /*<<< orphan*/  ixgbe_acquire_swfw_sync_X540 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_get_swfw_sync_semaphore (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync_X540 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync_semaphore (struct ixgbe_hw*) ; 

void ixgbe_init_swfw_sync_X540(struct ixgbe_hw *hw)
{
	u32 rmask;

	/* First try to grab the semaphore but we don't need to bother
	 * looking to see whether we got the lock or not since we do
	 * the same thing regardless of whether we got the lock or not.
	 * We got the lock - we release it.
	 * We timeout trying to get the lock - we force its release.
	 */
	ixgbe_get_swfw_sync_semaphore(hw);
	ixgbe_release_swfw_sync_semaphore(hw);

	/* Acquire and release all software resources. */
	rmask = IXGBE_GSSR_EEP_SM | IXGBE_GSSR_PHY0_SM |
		IXGBE_GSSR_PHY1_SM | IXGBE_GSSR_MAC_CSR_SM |
		IXGBE_GSSR_SW_MNG_SM;

	rmask |= IXGBE_GSSR_I2C_MASK;
	ixgbe_acquire_swfw_sync_X540(hw, rmask);
	ixgbe_release_swfw_sync_X540(hw, rmask);
}