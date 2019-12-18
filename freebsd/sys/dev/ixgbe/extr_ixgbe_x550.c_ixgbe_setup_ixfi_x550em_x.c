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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ (* read_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* write_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct ixgbe_mac_info {TYPE_1__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  lan_id; } ;
struct ixgbe_hw {TYPE_2__ bus; struct ixgbe_mac_info mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_KRM_DSP_TXFFE_STATE_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_KRM_DSP_TXFFE_STATE_5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_KRM_DSP_TXFFE_STATE_C0_EN ; 
 int /*<<< orphan*/  IXGBE_KRM_DSP_TXFFE_STATE_CO_ADAPT_EN ; 
 int /*<<< orphan*/  IXGBE_KRM_DSP_TXFFE_STATE_CP1_CN1_EN ; 
 int /*<<< orphan*/  IXGBE_KRM_RX_TRN_LINKUP_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_KRM_RX_TRN_LINKUP_CTRL_CONV_WO_PROTOCOL ; 
 int /*<<< orphan*/  IXGBE_KRM_TX_COEFF_CTRL_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_KRM_TX_COEFF_CTRL_1_CMINUS1_OVRRD_EN ; 
 int /*<<< orphan*/  IXGBE_KRM_TX_COEFF_CTRL_1_CPLUS1_OVRRD_EN ; 
 int /*<<< orphan*/  IXGBE_KRM_TX_COEFF_CTRL_1_CZERO_EN ; 
 int /*<<< orphan*/  IXGBE_KRM_TX_COEFF_CTRL_1_OVRRD_EN ; 
 int /*<<< orphan*/  IXGBE_SB_IOSF_TARGET_KR_PHY ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub7 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub8 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_setup_ixfi_x550em_x(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	s32 status;
	u32 reg_val;

	/* Disable training protocol FSM. */
	status = mac->ops.read_iosf_sb_reg(hw,
				IXGBE_KRM_RX_TRN_LINKUP_CTRL(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	if (status != IXGBE_SUCCESS)
		return status;
	reg_val |= IXGBE_KRM_RX_TRN_LINKUP_CTRL_CONV_WO_PROTOCOL;
	status = mac->ops.write_iosf_sb_reg(hw,
				IXGBE_KRM_RX_TRN_LINKUP_CTRL(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	if (status != IXGBE_SUCCESS)
		return status;

	/* Disable Flex from training TXFFE. */
	status = mac->ops.read_iosf_sb_reg(hw,
				IXGBE_KRM_DSP_TXFFE_STATE_4(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	if (status != IXGBE_SUCCESS)
		return status;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_C0_EN;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_CP1_CN1_EN;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_CO_ADAPT_EN;
	status = mac->ops.write_iosf_sb_reg(hw,
				IXGBE_KRM_DSP_TXFFE_STATE_4(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	if (status != IXGBE_SUCCESS)
		return status;
	status = mac->ops.read_iosf_sb_reg(hw,
				IXGBE_KRM_DSP_TXFFE_STATE_5(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	if (status != IXGBE_SUCCESS)
		return status;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_C0_EN;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_CP1_CN1_EN;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_CO_ADAPT_EN;
	status = mac->ops.write_iosf_sb_reg(hw,
				IXGBE_KRM_DSP_TXFFE_STATE_5(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	if (status != IXGBE_SUCCESS)
		return status;

	/* Enable override for coefficients. */
	status = mac->ops.read_iosf_sb_reg(hw,
				IXGBE_KRM_TX_COEFF_CTRL_1(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	if (status != IXGBE_SUCCESS)
		return status;
	reg_val |= IXGBE_KRM_TX_COEFF_CTRL_1_OVRRD_EN;
	reg_val |= IXGBE_KRM_TX_COEFF_CTRL_1_CZERO_EN;
	reg_val |= IXGBE_KRM_TX_COEFF_CTRL_1_CPLUS1_OVRRD_EN;
	reg_val |= IXGBE_KRM_TX_COEFF_CTRL_1_CMINUS1_OVRRD_EN;
	status = mac->ops.write_iosf_sb_reg(hw,
				IXGBE_KRM_TX_COEFF_CTRL_1(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	return status;
}