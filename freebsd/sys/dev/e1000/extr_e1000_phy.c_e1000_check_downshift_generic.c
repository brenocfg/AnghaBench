#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_reg ) (struct e1000_hw*,int,int*) ;} ;
struct e1000_phy_info {int type; int speed_downgraded; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int FALSE ; 
 int IGP01E1000_PHY_LINK_HEALTH ; 
 int IGP01E1000_PLHR_SS_DOWNGRADE ; 
 int M88E1000_PHY_SPEC_STATUS ; 
 int M88E1000_PSSR_DOWNSHIFT ; 
#define  e1000_phy_82578 135 
#define  e1000_phy_bm 134 
#define  e1000_phy_gg82563 133 
#define  e1000_phy_i210 132 
#define  e1000_phy_igp 131 
#define  e1000_phy_igp_2 130 
#define  e1000_phy_igp_3 129 
#define  e1000_phy_m88 128 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int,int*) ; 

s32 e1000_check_downshift_generic(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, offset, mask;

	DEBUGFUNC("e1000_check_downshift_generic");

	switch (phy->type) {
	case e1000_phy_i210:
	case e1000_phy_m88:
	case e1000_phy_gg82563:
	case e1000_phy_bm:
	case e1000_phy_82578:
		offset = M88E1000_PHY_SPEC_STATUS;
		mask = M88E1000_PSSR_DOWNSHIFT;
		break;
	case e1000_phy_igp:
	case e1000_phy_igp_2:
	case e1000_phy_igp_3:
		offset = IGP01E1000_PHY_LINK_HEALTH;
		mask = IGP01E1000_PLHR_SS_DOWNGRADE;
		break;
	default:
		/* speed downshift not supported */
		phy->speed_downgraded = FALSE;
		return E1000_SUCCESS;
	}

	ret_val = phy->ops.read_reg(hw, offset, &phy_data);

	if (!ret_val)
		phy->speed_downgraded = !!(phy_data & mask);

	return ret_val;
}