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
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* write_reg_locked ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg_locked ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {scalar_t__ type; int revision; int addr; TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BM_PORT_GEN_CFG ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  HV_KMRN_FIFO_CTRLSTA ; 
 int /*<<< orphan*/  I82577_MSE_THRESHOLD ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PAGE_SELECT ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  PHY_REG (int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ e1000_k1_gig_workaround_hv (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_pchlan ; 
 scalar_t__ e1000_phy_82577 ; 
 scalar_t__ e1000_phy_82578 ; 
 int /*<<< orphan*/  e1000_phy_sw_reset_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_set_mdio_slow_mode_hv (struct e1000_hw*) ; 
 scalar_t__ e1000_write_emi_reg_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_write_phy_reg_mdic (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub4 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*) ; 
 scalar_t__ stub6 (struct e1000_hw*) ; 
 scalar_t__ stub7 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub8 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_hv_phy_workarounds_ich8lan(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;
	u16 phy_data;

	DEBUGFUNC("e1000_hv_phy_workarounds_ich8lan");

	if (hw->mac.type != e1000_pchlan)
		return E1000_SUCCESS;

	/* Set MDIO slow mode before any other MDIO access */
	if (hw->phy.type == e1000_phy_82577) {
		ret_val = e1000_set_mdio_slow_mode_hv(hw);
		if (ret_val)
			return ret_val;
	}

	if (((hw->phy.type == e1000_phy_82577) &&
	     ((hw->phy.revision == 1) || (hw->phy.revision == 2))) ||
	    ((hw->phy.type == e1000_phy_82578) && (hw->phy.revision == 1))) {
		/* Disable generation of early preamble */
		ret_val = hw->phy.ops.write_reg(hw, PHY_REG(769, 25), 0x4431);
		if (ret_val)
			return ret_val;

		/* Preamble tuning for SSC */
		ret_val = hw->phy.ops.write_reg(hw, HV_KMRN_FIFO_CTRLSTA,
						0xA204);
		if (ret_val)
			return ret_val;
	}

	if (hw->phy.type == e1000_phy_82578) {
		/* Return registers to default by doing a soft reset then
		 * writing 0x3140 to the control register.
		 */
		if (hw->phy.revision < 2) {
			e1000_phy_sw_reset_generic(hw);
			ret_val = hw->phy.ops.write_reg(hw, PHY_CONTROL,
							0x3140);
			if (ret_val)
				return ret_val;
		}
	}

	/* Select page 0 */
	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;

	hw->phy.addr = 1;
	ret_val = e1000_write_phy_reg_mdic(hw, IGP01E1000_PHY_PAGE_SELECT, 0);
	hw->phy.ops.release(hw);
	if (ret_val)
		return ret_val;

	/* Configure the K1 Si workaround during phy reset assuming there is
	 * link so that it disables K1 if link is in 1Gbps.
	 */
	ret_val = e1000_k1_gig_workaround_hv(hw, TRUE);
	if (ret_val)
		return ret_val;

	/* Workaround for link disconnects on a busy hub in half duplex */
	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;
	ret_val = hw->phy.ops.read_reg_locked(hw, BM_PORT_GEN_CFG, &phy_data);
	if (ret_val)
		goto release;
	ret_val = hw->phy.ops.write_reg_locked(hw, BM_PORT_GEN_CFG,
					       phy_data & 0x00FF);
	if (ret_val)
		goto release;

	/* set MSE higher to enable link to stay up when noise is high */
	ret_val = e1000_write_emi_reg_locked(hw, I82577_MSE_THRESHOLD, 0x0034);
release:
	hw->phy.ops.release(hw);

	return ret_val;
}