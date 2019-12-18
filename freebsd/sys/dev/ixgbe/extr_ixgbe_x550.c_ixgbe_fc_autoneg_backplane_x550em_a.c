#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  requested_mode; int /*<<< orphan*/  current_mode; int /*<<< orphan*/  fc_was_autonegged; scalar_t__ disable_fc_autoneg; } ;
struct TYPE_7__ {int /*<<< orphan*/  lan_id; } ;
struct TYPE_5__ {scalar_t__ (* read_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* check_link ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ fc; TYPE_3__ bus; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IXGBE_ERROR_SOFTWARE ; 
 int /*<<< orphan*/  IXGBE_ERROR_UNSUPPORTED ; 
 scalar_t__ IXGBE_ERR_FC_NOT_NEGOTIATED ; 
 int /*<<< orphan*/  IXGBE_KRM_AN_CNTL_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_KRM_AN_CNTL_1_ASM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_KRM_AN_CNTL_1_SYM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_KRM_LINK_S1 (int /*<<< orphan*/ ) ; 
 int IXGBE_KRM_LINK_S1_MAC_AN_COMPLETE ; 
 int /*<<< orphan*/  IXGBE_KRM_LP_BASE_PAGE_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_KRM_LP_BASE_PAGE_HIGH_ASM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_KRM_LP_BASE_PAGE_HIGH_SYM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_SB_IOSF_TARGET_KR_PHY ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ixgbe_negotiate_fc (struct ixgbe_hw*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void ixgbe_fc_autoneg_backplane_x550em_a(struct ixgbe_hw *hw)
{
	u32 link_s1, lp_an_page_low, an_cntl_1;
	s32 status = IXGBE_ERR_FC_NOT_NEGOTIATED;
	ixgbe_link_speed speed;
	bool link_up;

	/* AN should have completed when the cable was plugged in.
	 * Look for reasons to bail out.  Bail out if:
	 * - FC autoneg is disabled, or if
	 * - link is not up.
	 */
	if (hw->fc.disable_fc_autoneg) {
		ERROR_REPORT1(IXGBE_ERROR_UNSUPPORTED,
			     "Flow control autoneg is disabled");
		goto out;
	}

	hw->mac.ops.check_link(hw, &speed, &link_up, FALSE);
	if (!link_up) {
		ERROR_REPORT1(IXGBE_ERROR_SOFTWARE, "The link is down");
		goto out;
	}

	/* Check at auto-negotiation has completed */
	status = hw->mac.ops.read_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_S1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, &link_s1);

	if (status != IXGBE_SUCCESS ||
	    (link_s1 & IXGBE_KRM_LINK_S1_MAC_AN_COMPLETE) == 0) {
		DEBUGOUT("Auto-Negotiation did not complete\n");
		status = IXGBE_ERR_FC_NOT_NEGOTIATED;
		goto out;
	}

	/* Read the 10g AN autoc and LP ability registers and resolve
	 * local flow control settings accordingly
	 */
	status = hw->mac.ops.read_iosf_sb_reg(hw,
				IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &an_cntl_1);

	if (status != IXGBE_SUCCESS) {
		DEBUGOUT("Auto-Negotiation did not complete\n");
		goto out;
	}

	status = hw->mac.ops.read_iosf_sb_reg(hw,
				IXGBE_KRM_LP_BASE_PAGE_HIGH(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &lp_an_page_low);

	if (status != IXGBE_SUCCESS) {
		DEBUGOUT("Auto-Negotiation did not complete\n");
		goto out;
	}

	status = ixgbe_negotiate_fc(hw, an_cntl_1, lp_an_page_low,
				    IXGBE_KRM_AN_CNTL_1_SYM_PAUSE,
				    IXGBE_KRM_AN_CNTL_1_ASM_PAUSE,
				    IXGBE_KRM_LP_BASE_PAGE_HIGH_SYM_PAUSE,
				    IXGBE_KRM_LP_BASE_PAGE_HIGH_ASM_PAUSE);

out:
	if (status == IXGBE_SUCCESS) {
		hw->fc.fc_was_autonegged = TRUE;
	} else {
		hw->fc.fc_was_autonegged = FALSE;
		hw->fc.current_mode = hw->fc.requested_mode;
	}
}