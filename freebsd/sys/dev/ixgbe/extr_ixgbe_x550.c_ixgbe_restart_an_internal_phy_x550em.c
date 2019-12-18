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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  lan_id; } ;
struct TYPE_4__ {scalar_t__ (* write_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_3__ bus; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_KRM_LINK_CTRL_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_KRM_LINK_CTRL_1_TETH_AN_RESTART ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20_FW_AN_RESTART ; 
 int /*<<< orphan*/  IXGBE_SB_IOSF_TARGET_KR_PHY ; 
 scalar_t__ ixgbe_mac_X550EM_a ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_restart_an_internal_phy_x550em(struct ixgbe_hw *hw)
{
	s32 status;
	u32 link_ctrl;

	/* Restart auto-negotiation. */
	status = hw->mac.ops.read_iosf_sb_reg(hw,
				       IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
				       IXGBE_SB_IOSF_TARGET_KR_PHY, &link_ctrl);

	if (status) {
		DEBUGOUT("Auto-negotiation did not complete\n");
		return status;
	}

	link_ctrl |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_RESTART;
	status = hw->mac.ops.write_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, link_ctrl);

	if (hw->mac.type == ixgbe_mac_X550EM_a) {
		u32 flx_mask_st20;

		/* Indicate to FW that AN restart has been asserted */
		status = hw->mac.ops.read_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &flx_mask_st20);

		if (status) {
			DEBUGOUT("Auto-negotiation did not complete\n");
			return status;
		}

		flx_mask_st20 |= IXGBE_KRM_PMD_FLX_MASK_ST20_FW_AN_RESTART;
		status = hw->mac.ops.write_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, flx_mask_st20);
	}

	return status;
}