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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  lan_id; } ;
struct TYPE_4__ {scalar_t__ (* write_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_3__ bus; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_KRM_LINK_CTRL_1 (int /*<<< orphan*/ ) ; 
 int IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KR ; 
 int IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KX ; 
 int IXGBE_KRM_LINK_CTRL_1_TETH_AN_ENABLE ; 
 int /*<<< orphan*/  IXGBE_KRM_PMD_FLX_MASK_ST20 (int /*<<< orphan*/ ) ; 
 int IXGBE_KRM_PMD_FLX_MASK_ST20_AN37_EN ; 
 int IXGBE_KRM_PMD_FLX_MASK_ST20_AN_EN ; 
 int IXGBE_KRM_PMD_FLX_MASK_ST20_SGMII_EN ; 
 int IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_AN ; 
 int IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_MASK ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  IXGBE_SB_IOSF_TARGET_KR_PHY ; 
 scalar_t__ ixgbe_mac_X550EM_a ; 
 scalar_t__ ixgbe_restart_an_internal_phy_x550em (struct ixgbe_hw*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbe_setup_kr_speed_x550em(struct ixgbe_hw *hw,
				       ixgbe_link_speed speed)
{
	s32 status;
	u32 reg_val;

	status = hw->mac.ops.read_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	if (status)
		return status;

	reg_val |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_ENABLE;
	reg_val &= ~(IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KR |
		     IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KX);

	/* Advertise 10G support. */
	if (speed & IXGBE_LINK_SPEED_10GB_FULL)
		reg_val |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KR;

	/* Advertise 1G support. */
	if (speed & IXGBE_LINK_SPEED_1GB_FULL)
		reg_val |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KX;

	status = hw->mac.ops.write_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);

	if (hw->mac.type == ixgbe_mac_X550EM_a) {
		/* Set lane mode  to KR auto negotiation */
		status = hw->mac.ops.read_iosf_sb_reg(hw,
				    IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				    IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);

		if (status)
			return status;

		reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_MASK;
		reg_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_AN;
		reg_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_AN_EN;
		reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_AN37_EN;
		reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SGMII_EN;

		status = hw->mac.ops.write_iosf_sb_reg(hw,
				    IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				    IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	}

	return ixgbe_restart_an_internal_phy_x550em(hw);
}