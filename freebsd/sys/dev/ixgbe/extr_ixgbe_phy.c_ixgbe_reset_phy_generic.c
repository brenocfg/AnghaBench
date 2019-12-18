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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* check_overtemp ) (struct ixgbe_hw*) ;scalar_t__ (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* write_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ ops; int /*<<< orphan*/  reset_if_overtemp; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  ERROR_REPORT1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IXGBE_ERROR_POLLING ; 
 scalar_t__ IXGBE_ERR_OVERTEMP ; 
 scalar_t__ IXGBE_ERR_RESET_FAILED ; 
 int /*<<< orphan*/  IXGBE_MDIO_PHY_XS_CONTROL ; 
 int /*<<< orphan*/  IXGBE_MDIO_PHY_XS_DEV_TYPE ; 
 int IXGBE_MDIO_PHY_XS_RESET ; 
 int /*<<< orphan*/  IXGBE_MDIO_PMA_PMD_DEV_TYPE ; 
 int /*<<< orphan*/  IXGBE_MDIO_TX_VENDOR_ALARMS_3 ; 
 int IXGBE_MDIO_TX_VENDOR_ALARMS_3_RST_MASK ; 
 scalar_t__ IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_check_reset_blocked (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_identify_phy_generic (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_phy_none ; 
 scalar_t__ ixgbe_phy_unknown ; 
 scalar_t__ ixgbe_phy_x550em_ext_t ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 ixgbe_reset_phy_generic(struct ixgbe_hw *hw)
{
	u32 i;
	u16 ctrl = 0;
	s32 status = IXGBE_SUCCESS;

	DEBUGFUNC("ixgbe_reset_phy_generic");

	if (hw->phy.type == ixgbe_phy_unknown)
		status = ixgbe_identify_phy_generic(hw);

	if (status != IXGBE_SUCCESS || hw->phy.type == ixgbe_phy_none)
		goto out;

	/* Don't reset PHY if it's shut down due to overtemp. */
	if (!hw->phy.reset_if_overtemp &&
	    (IXGBE_ERR_OVERTEMP == hw->phy.ops.check_overtemp(hw)))
		goto out;

	/* Blocked by MNG FW so bail */
	if (ixgbe_check_reset_blocked(hw))
		goto out;

	/*
	 * Perform soft PHY reset to the PHY_XS.
	 * This will cause a soft reset to the PHY
	 */
	hw->phy.ops.write_reg(hw, IXGBE_MDIO_PHY_XS_CONTROL,
			      IXGBE_MDIO_PHY_XS_DEV_TYPE,
			      IXGBE_MDIO_PHY_XS_RESET);

	/*
	 * Poll for reset bit to self-clear indicating reset is complete.
	 * Some PHYs could take up to 3 seconds to complete and need about
	 * 1.7 usec delay after the reset is complete.
	 */
	for (i = 0; i < 30; i++) {
		msec_delay(100);
		if (hw->phy.type == ixgbe_phy_x550em_ext_t) {
			status = hw->phy.ops.read_reg(hw,
						  IXGBE_MDIO_TX_VENDOR_ALARMS_3,
						  IXGBE_MDIO_PMA_PMD_DEV_TYPE,
						  &ctrl);
			if (status != IXGBE_SUCCESS)
				return status;

			if (ctrl & IXGBE_MDIO_TX_VENDOR_ALARMS_3_RST_MASK) {
				usec_delay(2);
				break;
			}
		} else {
			status = hw->phy.ops.read_reg(hw,
						     IXGBE_MDIO_PHY_XS_CONTROL,
						     IXGBE_MDIO_PHY_XS_DEV_TYPE,
						     &ctrl);
			if (status != IXGBE_SUCCESS)
				return status;

			if (!(ctrl & IXGBE_MDIO_PHY_XS_RESET)) {
				usec_delay(2);
				break;
			}
		}
	}

	if (ctrl & IXGBE_MDIO_PHY_XS_RESET) {
		status = IXGBE_ERR_RESET_FAILED;
		ERROR_REPORT1(IXGBE_ERROR_POLLING,
			     "PHY reset polling failed to complete.\n");
	}

out:
	return status;
}