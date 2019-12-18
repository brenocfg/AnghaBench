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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ (* stop_adapter ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* init_rx_addrs ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* get_mac_addr ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_analog_reg8 ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read_analog_reg8 ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_8__ {int flags; scalar_t__ orig_link_settings_stored; int orig_autoc; TYPE_3__ ops; int /*<<< orphan*/  perm_addr; } ;
struct TYPE_5__ {scalar_t__ (* init ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* reset ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {scalar_t__ reset_disable; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ mac; TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_10G ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_1G ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_AN ; 
 int /*<<< orphan*/  IXGBE_ATLAS_PDN_LPBK ; 
 int IXGBE_ATLAS_PDN_TX_10G_QL_ALL ; 
 int IXGBE_ATLAS_PDN_TX_1G_QL_ALL ; 
 int IXGBE_ATLAS_PDN_TX_AN_QL_ALL ; 
 int IXGBE_ATLAS_PDN_TX_REG_EN ; 
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 int /*<<< orphan*/  IXGBE_CTRL ; 
 int IXGBE_CTRL_RST ; 
 scalar_t__ IXGBE_ERR_RESET_FAILED ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_PRESENT ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_SUPPORTED ; 
 int IXGBE_FLAGS_DOUBLE_RESET_REQUIRED ; 
 int /*<<< orphan*/  IXGBE_GHECCR ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub10 (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub11 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub12 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub13 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub8 (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct ixgbe_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 ixgbe_reset_hw_82598(struct ixgbe_hw *hw)
{
	s32 status = IXGBE_SUCCESS;
	s32 phy_status = IXGBE_SUCCESS;
	u32 ctrl;
	u32 gheccr;
	u32 i;
	u32 autoc;
	u8  analog_val;

	DEBUGFUNC("ixgbe_reset_hw_82598");

	/* Call adapter stop to disable tx/rx and clear interrupts */
	status = hw->mac.ops.stop_adapter(hw);
	if (status != IXGBE_SUCCESS)
		goto reset_hw_out;

	/*
	 * Power up the Atlas Tx lanes if they are currently powered down.
	 * Atlas Tx lanes are powered down for MAC loopback tests, but
	 * they are not automatically restored on reset.
	 */
	hw->mac.ops.read_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK, &analog_val);
	if (analog_val & IXGBE_ATLAS_PDN_TX_REG_EN) {
		/* Enable Tx Atlas so packets can be transmitted again */
		hw->mac.ops.read_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK,
					     &analog_val);
		analog_val &= ~IXGBE_ATLAS_PDN_TX_REG_EN;
		hw->mac.ops.write_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK,
					      analog_val);

		hw->mac.ops.read_analog_reg8(hw, IXGBE_ATLAS_PDN_10G,
					     &analog_val);
		analog_val &= ~IXGBE_ATLAS_PDN_TX_10G_QL_ALL;
		hw->mac.ops.write_analog_reg8(hw, IXGBE_ATLAS_PDN_10G,
					      analog_val);

		hw->mac.ops.read_analog_reg8(hw, IXGBE_ATLAS_PDN_1G,
					     &analog_val);
		analog_val &= ~IXGBE_ATLAS_PDN_TX_1G_QL_ALL;
		hw->mac.ops.write_analog_reg8(hw, IXGBE_ATLAS_PDN_1G,
					      analog_val);

		hw->mac.ops.read_analog_reg8(hw, IXGBE_ATLAS_PDN_AN,
					     &analog_val);
		analog_val &= ~IXGBE_ATLAS_PDN_TX_AN_QL_ALL;
		hw->mac.ops.write_analog_reg8(hw, IXGBE_ATLAS_PDN_AN,
					      analog_val);
	}

	/* Reset PHY */
	if (hw->phy.reset_disable == FALSE) {
		/* PHY ops must be identified and initialized prior to reset */

		/* Init PHY and function pointers, perform SFP setup */
		phy_status = hw->phy.ops.init(hw);
		if (phy_status == IXGBE_ERR_SFP_NOT_SUPPORTED)
			goto reset_hw_out;
		if (phy_status == IXGBE_ERR_SFP_NOT_PRESENT)
			goto mac_reset_top;

		hw->phy.ops.reset(hw);
	}

mac_reset_top:
	/*
	 * Issue global reset to the MAC.  This needs to be a SW reset.
	 * If link reset is used, it might reset the MAC when mng is using it
	 */
	ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL) | IXGBE_CTRL_RST;
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, ctrl);
	IXGBE_WRITE_FLUSH(hw);

	/* Poll for reset bit to self-clear indicating reset is complete */
	for (i = 0; i < 10; i++) {
		usec_delay(1);
		ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL);
		if (!(ctrl & IXGBE_CTRL_RST))
			break;
	}
	if (ctrl & IXGBE_CTRL_RST) {
		status = IXGBE_ERR_RESET_FAILED;
		DEBUGOUT("Reset polling failed to complete.\n");
	}

	msec_delay(50);

	/*
	 * Double resets are required for recovery from certain error
	 * conditions.  Between resets, it is necessary to stall to allow time
	 * for any pending HW events to complete.
	 */
	if (hw->mac.flags & IXGBE_FLAGS_DOUBLE_RESET_REQUIRED) {
		hw->mac.flags &= ~IXGBE_FLAGS_DOUBLE_RESET_REQUIRED;
		goto mac_reset_top;
	}

	gheccr = IXGBE_READ_REG(hw, IXGBE_GHECCR);
	gheccr &= ~((1 << 21) | (1 << 18) | (1 << 9) | (1 << 6));
	IXGBE_WRITE_REG(hw, IXGBE_GHECCR, gheccr);

	/*
	 * Store the original AUTOC value if it has not been
	 * stored off yet.  Otherwise restore the stored original
	 * AUTOC value since the reset operation sets back to deaults.
	 */
	autoc = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	if (hw->mac.orig_link_settings_stored == FALSE) {
		hw->mac.orig_autoc = autoc;
		hw->mac.orig_link_settings_stored = TRUE;
	} else if (autoc != hw->mac.orig_autoc) {
		IXGBE_WRITE_REG(hw, IXGBE_AUTOC, hw->mac.orig_autoc);
	}

	/* Store the permanent mac address */
	hw->mac.ops.get_mac_addr(hw, hw->mac.perm_addr);

	/*
	 * Store MAC address from RAR0, clear receive address registers, and
	 * clear the multicast table
	 */
	hw->mac.ops.init_rx_addrs(hw);

reset_hw_out:
	if (phy_status != IXGBE_SUCCESS)
		status = phy_status;

	return status;
}