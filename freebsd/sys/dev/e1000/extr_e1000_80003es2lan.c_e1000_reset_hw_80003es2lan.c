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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_RST ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_IBIST_DISABLE ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_INBAND_PARAM ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int E1000_TCTL_PSP ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_acquire_phy_80003es2lan (struct e1000_hw*) ; 
 scalar_t__ e1000_check_alt_mac_addr_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_disable_pcie_master_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_get_auto_rd_done_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_read_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_release_phy_80003es2lan (struct e1000_hw*) ; 
 scalar_t__ e1000_write_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

__attribute__((used)) static s32 e1000_reset_hw_80003es2lan(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val;
	u16 kum_reg_data;

	DEBUGFUNC("e1000_reset_hw_80003es2lan");

	/* Prevent the PCI-E bus from sticking if there is no TLP connection
	 * on the last TLP read/write transaction when MAC is reset.
	 */
	ret_val = e1000_disable_pcie_master_generic(hw);
	if (ret_val)
		DEBUGOUT("PCI-E Master disable polling has failed.\n");

	DEBUGOUT("Masking off all interrupts\n");
	E1000_WRITE_REG(hw, E1000_IMC, 0xffffffff);

	E1000_WRITE_REG(hw, E1000_RCTL, 0);
	E1000_WRITE_REG(hw, E1000_TCTL, E1000_TCTL_PSP);
	E1000_WRITE_FLUSH(hw);

	msec_delay(10);

	ctrl = E1000_READ_REG(hw, E1000_CTRL);

	ret_val = e1000_acquire_phy_80003es2lan(hw);
	if (ret_val)
		return ret_val;

	DEBUGOUT("Issuing a global reset to MAC\n");
	E1000_WRITE_REG(hw, E1000_CTRL, ctrl | E1000_CTRL_RST);
	e1000_release_phy_80003es2lan(hw);

	/* Disable IBIST slave mode (far-end loopback) */
	ret_val = e1000_read_kmrn_reg_80003es2lan(hw,
				E1000_KMRNCTRLSTA_INBAND_PARAM, &kum_reg_data);
	if (!ret_val) {
		kum_reg_data |= E1000_KMRNCTRLSTA_IBIST_DISABLE;
		ret_val = e1000_write_kmrn_reg_80003es2lan(hw,
						 E1000_KMRNCTRLSTA_INBAND_PARAM,
						 kum_reg_data);
		if (ret_val)
			DEBUGOUT("Error disabling far-end loopback\n");
	} else
		DEBUGOUT("Error disabling far-end loopback\n");

	ret_val = e1000_get_auto_rd_done_generic(hw);
	if (ret_val)
		/* We don't want to continue accessing MAC registers. */
		return ret_val;

	/* Clear any pending interrupt events. */
	E1000_WRITE_REG(hw, E1000_IMC, 0xffffffff);
	E1000_READ_REG(hw, E1000_ICR);

	return e1000_check_alt_mac_addr_generic(hw);
}