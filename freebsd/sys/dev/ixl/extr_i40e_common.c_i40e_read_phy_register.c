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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int device_id; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
#define  I40E_DEV_ID_10G_BASE_T 133 
#define  I40E_DEV_ID_10G_BASE_T4 132 
#define  I40E_DEV_ID_10G_BASE_T_X722 131 
#define  I40E_DEV_ID_1G_BASE_T_X722 130 
#define  I40E_DEV_ID_25G_B 129 
#define  I40E_DEV_ID_25G_SFP28 128 
 int I40E_ERR_UNKNOWN_PHY ; 
 int i40e_read_phy_register_clause22 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int i40e_read_phy_register_clause45 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

enum i40e_status_code i40e_read_phy_register(struct i40e_hw *hw,
				u8 page, u16 reg, u8 phy_addr, u16 *value)
{
	enum i40e_status_code status;

	switch (hw->device_id) {
	case I40E_DEV_ID_1G_BASE_T_X722:
		status = i40e_read_phy_register_clause22(hw, reg, phy_addr,
							 value);
		break;
	case I40E_DEV_ID_10G_BASE_T:
	case I40E_DEV_ID_10G_BASE_T4:
	case I40E_DEV_ID_10G_BASE_T_X722:
	case I40E_DEV_ID_25G_B:
	case I40E_DEV_ID_25G_SFP28:
		status = i40e_read_phy_register_clause45(hw, page, reg,
							 phy_addr, value);
		break;
	default:
		status = I40E_ERR_UNKNOWN_PHY;
		break;
	}

	return status;
}