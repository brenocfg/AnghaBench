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
struct TYPE_6__ {int /*<<< orphan*/  phy_semaphore_mask; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  lan_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_lan_id ) (struct ixgbe_hw*) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct ixgbe_hw {int device_id; TYPE_2__ phy; TYPE_1__ bus; TYPE_4__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  IXGBE_DEV_ID_X550EM_A_10G_T 140 
#define  IXGBE_DEV_ID_X550EM_A_1G_T 139 
#define  IXGBE_DEV_ID_X550EM_A_1G_T_L 138 
#define  IXGBE_DEV_ID_X550EM_A_KR 137 
#define  IXGBE_DEV_ID_X550EM_A_KR_L 136 
#define  IXGBE_DEV_ID_X550EM_A_SFP 135 
#define  IXGBE_DEV_ID_X550EM_A_SFP_N 134 
#define  IXGBE_DEV_ID_X550EM_X_10G_T 133 
#define  IXGBE_DEV_ID_X550EM_X_1G_T 132 
#define  IXGBE_DEV_ID_X550EM_X_KR 131 
#define  IXGBE_DEV_ID_X550EM_X_KX4 130 
#define  IXGBE_DEV_ID_X550EM_X_SFP 129 
#define  IXGBE_DEV_ID_X550EM_X_XFI 128 
 int /*<<< orphan*/  IXGBE_GSSR_PHY0_SM ; 
 int /*<<< orphan*/  IXGBE_GSSR_PHY1_SM ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_check_cs4227 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_identify_module_generic (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_identify_phy_generic (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_phy_ext_1g_t ; 
 int /*<<< orphan*/  ixgbe_phy_fw ; 
 int /*<<< orphan*/  ixgbe_phy_x550em_kr ; 
 int /*<<< orphan*/  ixgbe_phy_x550em_kx4 ; 
 int /*<<< orphan*/  ixgbe_phy_x550em_xfi ; 
 int /*<<< orphan*/  ixgbe_read_mng_if_sel_x550em (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_setup_mux_ctl (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_identify_phy_x550em(struct ixgbe_hw *hw)
{
	hw->mac.ops.set_lan_id(hw);

	ixgbe_read_mng_if_sel_x550em(hw);

	switch (hw->device_id) {
	case IXGBE_DEV_ID_X550EM_A_SFP:
		return ixgbe_identify_module_generic(hw);
	case IXGBE_DEV_ID_X550EM_X_SFP:
		/* set up for CS4227 usage */
		ixgbe_setup_mux_ctl(hw);
		ixgbe_check_cs4227(hw);
		/* Fallthrough */

	case IXGBE_DEV_ID_X550EM_A_SFP_N:
		return ixgbe_identify_module_generic(hw);
		break;
	case IXGBE_DEV_ID_X550EM_X_KX4:
		hw->phy.type = ixgbe_phy_x550em_kx4;
		break;
	case IXGBE_DEV_ID_X550EM_X_XFI:
		hw->phy.type = ixgbe_phy_x550em_xfi;
		break;
	case IXGBE_DEV_ID_X550EM_X_KR:
	case IXGBE_DEV_ID_X550EM_A_KR:
	case IXGBE_DEV_ID_X550EM_A_KR_L:
		hw->phy.type = ixgbe_phy_x550em_kr;
		break;
	case IXGBE_DEV_ID_X550EM_A_10G_T:
	case IXGBE_DEV_ID_X550EM_X_10G_T:
		return ixgbe_identify_phy_generic(hw);
	case IXGBE_DEV_ID_X550EM_X_1G_T:
		hw->phy.type = ixgbe_phy_ext_1g_t;
		break;
	case IXGBE_DEV_ID_X550EM_A_1G_T:
	case IXGBE_DEV_ID_X550EM_A_1G_T_L:
		hw->phy.type = ixgbe_phy_fw;
		if (hw->bus.lan_id)
			hw->phy.phy_semaphore_mask |= IXGBE_GSSR_PHY1_SM;
		else
			hw->phy.phy_semaphore_mask |= IXGBE_GSSR_PHY0_SM;
		break;
	default:
		break;
	}
	return IXGBE_SUCCESS;
}