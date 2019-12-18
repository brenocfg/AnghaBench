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
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset ) (struct e1000_hw*) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct e1000_dev_spec_ich8lan {int /*<<< orphan*/  kmrn_lock_loss_workaround_enabled; } ;
struct TYPE_4__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ dev_spec; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ E1000_ERR_PHY ; 
 int /*<<< orphan*/  E1000_PHY_CTRL ; 
 int E1000_PHY_CTRL_GBE_DISABLE ; 
 int E1000_PHY_CTRL_NOND0A_GBE_DISABLE ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IGP3_KMRN_DIAG ; 
 int IGP3_KMRN_DIAG_PCS_LOCK_LOSS ; 
 int /*<<< orphan*/  e1000_gig_downshift_workaround_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_phy_has_link_generic (struct e1000_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msec_delay_irq (int) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_kmrn_lock_loss_workaround_ich8lan(struct e1000_hw *hw)
{
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 phy_ctrl;
	s32 ret_val;
	u16 i, data;
	bool link;

	DEBUGFUNC("e1000_kmrn_lock_loss_workaround_ich8lan");

	if (!dev_spec->kmrn_lock_loss_workaround_enabled)
		return E1000_SUCCESS;

	/* Make sure link is up before proceeding.  If not just return.
	 * Attempting this while link is negotiating fouled up link
	 * stability
	 */
	ret_val = e1000_phy_has_link_generic(hw, 1, 0, &link);
	if (!link)
		return E1000_SUCCESS;

	for (i = 0; i < 10; i++) {
		/* read once to clear */
		ret_val = hw->phy.ops.read_reg(hw, IGP3_KMRN_DIAG, &data);
		if (ret_val)
			return ret_val;
		/* and again to get new status */
		ret_val = hw->phy.ops.read_reg(hw, IGP3_KMRN_DIAG, &data);
		if (ret_val)
			return ret_val;

		/* check for PCS lock */
		if (!(data & IGP3_KMRN_DIAG_PCS_LOCK_LOSS))
			return E1000_SUCCESS;

		/* Issue PHY reset */
		hw->phy.ops.reset(hw);
		msec_delay_irq(5);
	}
	/* Disable GigE link negotiation */
	phy_ctrl = E1000_READ_REG(hw, E1000_PHY_CTRL);
	phy_ctrl |= (E1000_PHY_CTRL_GBE_DISABLE |
		     E1000_PHY_CTRL_NOND0A_GBE_DISABLE);
	E1000_WRITE_REG(hw, E1000_PHY_CTRL, phy_ctrl);

	/* Call gig speed drop workaround on Gig disable before accessing
	 * any PHY registers
	 */
	e1000_gig_downshift_workaround_ich8lan(hw);

	/* unable to acquire PCS lock */
	return -E1000_ERR_PHY;
}