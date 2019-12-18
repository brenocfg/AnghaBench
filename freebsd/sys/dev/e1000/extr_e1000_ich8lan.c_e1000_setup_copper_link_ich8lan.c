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
struct TYPE_3__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {int type; TYPE_1__ ops; int /*<<< orphan*/  mdix; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_FRCDPX ; 
 int E1000_CTRL_FRCSPD ; 
 int E1000_CTRL_SLU ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_INBAND_PARAM ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_TIMEOUTS ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IFE_PHY_MDIX_CONTROL ; 
 int IFE_PMC_AUTO_MDIX ; 
 int IFE_PMC_FORCE_MDIX ; 
 scalar_t__ e1000_copper_link_setup_82577 (struct e1000_hw*) ; 
 scalar_t__ e1000_copper_link_setup_igp (struct e1000_hw*) ; 
 scalar_t__ e1000_copper_link_setup_m88 (struct e1000_hw*) ; 
#define  e1000_phy_82577 133 
#define  e1000_phy_82578 132 
#define  e1000_phy_82579 131 
#define  e1000_phy_bm 130 
#define  e1000_phy_ife 129 
#define  e1000_phy_igp_3 128 
 scalar_t__ e1000_read_kmrn_reg_generic (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_setup_copper_link_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_write_kmrn_reg_generic (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_setup_copper_link_ich8lan(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val;
	u16 reg_data;

	DEBUGFUNC("e1000_setup_copper_link_ich8lan");

	ctrl = E1000_READ_REG(hw, E1000_CTRL);
	ctrl |= E1000_CTRL_SLU;
	ctrl &= ~(E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	E1000_WRITE_REG(hw, E1000_CTRL, ctrl);

	/* Set the mac to wait the maximum time between each iteration
	 * and increase the max iterations when polling the phy;
	 * this fixes erroneous timeouts at 10Mbps.
	 */
	ret_val = e1000_write_kmrn_reg_generic(hw, E1000_KMRNCTRLSTA_TIMEOUTS,
					       0xFFFF);
	if (ret_val)
		return ret_val;
	ret_val = e1000_read_kmrn_reg_generic(hw,
					      E1000_KMRNCTRLSTA_INBAND_PARAM,
					      &reg_data);
	if (ret_val)
		return ret_val;
	reg_data |= 0x3F;
	ret_val = e1000_write_kmrn_reg_generic(hw,
					       E1000_KMRNCTRLSTA_INBAND_PARAM,
					       reg_data);
	if (ret_val)
		return ret_val;

	switch (hw->phy.type) {
	case e1000_phy_igp_3:
		ret_val = e1000_copper_link_setup_igp(hw);
		if (ret_val)
			return ret_val;
		break;
	case e1000_phy_bm:
	case e1000_phy_82578:
		ret_val = e1000_copper_link_setup_m88(hw);
		if (ret_val)
			return ret_val;
		break;
	case e1000_phy_82577:
	case e1000_phy_82579:
		ret_val = e1000_copper_link_setup_82577(hw);
		if (ret_val)
			return ret_val;
		break;
	case e1000_phy_ife:
		ret_val = hw->phy.ops.read_reg(hw, IFE_PHY_MDIX_CONTROL,
					       &reg_data);
		if (ret_val)
			return ret_val;

		reg_data &= ~IFE_PMC_AUTO_MDIX;

		switch (hw->phy.mdix) {
		case 1:
			reg_data &= ~IFE_PMC_FORCE_MDIX;
			break;
		case 2:
			reg_data |= IFE_PMC_FORCE_MDIX;
			break;
		case 0:
		default:
			reg_data |= IFE_PMC_AUTO_MDIX;
			break;
		}
		ret_val = hw->phy.ops.write_reg(hw, IFE_PHY_MDIX_CONTROL,
						reg_data);
		if (ret_val)
			return ret_val;
		break;
	default:
		break;
	}

	return e1000_setup_copper_link_generic(hw);
}