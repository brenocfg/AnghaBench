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
struct TYPE_2__ {scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct e1000_phy_info {int polarity_correction; int is_mdix; void* remote_rx; void* local_rx; int /*<<< orphan*/  cable_length; TYPE_1__ ops; int /*<<< orphan*/  cable_polarity; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CABLE_LENGTH_UNDEFINED ; 
 scalar_t__ E1000_ERR_CONFIG ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  IFE_PHY_MDIX_CONTROL ; 
 int /*<<< orphan*/  IFE_PHY_SPECIAL_CONTROL ; 
 int IFE_PMC_MDIX_STATUS ; 
 int IFE_PSC_AUTO_POLARITY_DISABLE ; 
 int IFE_PSC_FORCE_POLARITY ; 
 void* e1000_1000t_rx_status_undefined ; 
 scalar_t__ e1000_check_polarity_ife (struct e1000_hw*) ; 
 scalar_t__ e1000_phy_has_link_generic (struct e1000_hw*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e1000_rev_polarity_normal ; 
 int /*<<< orphan*/  e1000_rev_polarity_reversed ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 

s32 e1000_get_phy_info_ife(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	bool link;

	DEBUGFUNC("e1000_get_phy_info_ife");

	ret_val = e1000_phy_has_link_generic(hw, 1, 0, &link);
	if (ret_val)
		return ret_val;

	if (!link) {
		DEBUGOUT("Phy info is only valid if link is up\n");
		return -E1000_ERR_CONFIG;
	}

	ret_val = phy->ops.read_reg(hw, IFE_PHY_SPECIAL_CONTROL, &data);
	if (ret_val)
		return ret_val;
	phy->polarity_correction = !(data & IFE_PSC_AUTO_POLARITY_DISABLE);

	if (phy->polarity_correction) {
		ret_val = e1000_check_polarity_ife(hw);
		if (ret_val)
			return ret_val;
	} else {
		/* Polarity is forced */
		phy->cable_polarity = ((data & IFE_PSC_FORCE_POLARITY)
				       ? e1000_rev_polarity_reversed
				       : e1000_rev_polarity_normal);
	}

	ret_val = phy->ops.read_reg(hw, IFE_PHY_MDIX_CONTROL, &data);
	if (ret_val)
		return ret_val;

	phy->is_mdix = !!(data & IFE_PMC_MDIX_STATUS);

	/* The following parameters are undefined for 10/100 operation. */
	phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
	phy->local_rx = e1000_1000t_rx_status_undefined;
	phy->remote_rx = e1000_1000t_rx_status_undefined;

	return E1000_SUCCESS;
}