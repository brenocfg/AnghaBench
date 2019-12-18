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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct TYPE_4__ {size_t mcft_size; int mc_filter_type; int /*<<< orphan*/ * mta_shadow; } ;
struct TYPE_3__ {size_t num_mc_addrs; scalar_t__ mta_in_use; } ;
struct ixgbe_hw {TYPE_2__ mac; TYPE_1__ addr_ctrl; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  (* ixgbe_mc_addr_itr ) (struct ixgbe_hw*,int /*<<< orphan*/ **,size_t*) ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_MCSTCTRL ; 
 int IXGBE_MCSTCTRL_MFE ; 
 int /*<<< orphan*/  IXGBE_MTA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG_ARRAY (struct ixgbe_hw*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_set_mta (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

s32 ixgbe_update_mc_addr_list_generic(struct ixgbe_hw *hw, u8 *mc_addr_list,
				      u32 mc_addr_count, ixgbe_mc_addr_itr next,
				      bool clear)
{
	u32 i;
	u32 vmdq;

	DEBUGFUNC("ixgbe_update_mc_addr_list_generic");

	/*
	 * Set the new number of MC addresses that we are being requested to
	 * use.
	 */
	hw->addr_ctrl.num_mc_addrs = mc_addr_count;
	hw->addr_ctrl.mta_in_use = 0;

	/* Clear mta_shadow */
	if (clear) {
		DEBUGOUT(" Clearing MTA\n");
		memset(&hw->mac.mta_shadow, 0, sizeof(hw->mac.mta_shadow));
	}

	/* Update mta_shadow */
	for (i = 0; i < mc_addr_count; i++) {
		DEBUGOUT(" Adding the multicast addresses:\n");
		ixgbe_set_mta(hw, next(hw, &mc_addr_list, &vmdq));
	}

	/* Enable mta */
	for (i = 0; i < hw->mac.mcft_size; i++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_MTA(0), i,
				      hw->mac.mta_shadow[i]);

	if (hw->addr_ctrl.mta_in_use > 0)
		IXGBE_WRITE_REG(hw, IXGBE_MCSTCTRL,
				IXGBE_MCSTCTRL_MFE | hw->mac.mc_filter_type);

	DEBUGOUT("ixgbe_update_mc_addr_list_generic Complete\n");
	return IXGBE_SUCCESS;
}