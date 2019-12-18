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
struct TYPE_3__ {int (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/  setup_eee; int /*<<< orphan*/ * setup_fc; int /*<<< orphan*/  fc_autoneg; int /*<<< orphan*/  release_swfw_sync; int /*<<< orphan*/  acquire_swfw_sync; int /*<<< orphan*/  write_iosf_sb_reg; int /*<<< orphan*/  read_iosf_sb_reg; } ;
struct ixgbe_mac_info {TYPE_1__ ops; } ;
struct TYPE_4__ {int eee_speeds_supported; int eee_speeds_advertised; } ;
struct ixgbe_hw {int device_id; TYPE_2__ phy; struct ixgbe_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
#define  IXGBE_DEV_ID_X550EM_A_1G_T 131 
#define  IXGBE_DEV_ID_X550EM_A_1G_T_L 130 
 int IXGBE_DEV_ID_X550EM_A_SGMII ; 
 int IXGBE_DEV_ID_X550EM_A_SGMII_L ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  ixgbe_acquire_swfw_sync_X550a ; 
 int /*<<< orphan*/  ixgbe_fc_autoneg_backplane_x550em_a ; 
 int /*<<< orphan*/  ixgbe_fc_autoneg_fiber_x550em_a ; 
 int /*<<< orphan*/ * ixgbe_fc_autoneg_fw ; 
 int /*<<< orphan*/  ixgbe_fc_autoneg_sgmii_x550em_a ; 
 int /*<<< orphan*/  ixgbe_init_ops_X550EM (struct ixgbe_hw*) ; 
#define  ixgbe_media_type_backplane 129 
#define  ixgbe_media_type_fiber 128 
 int /*<<< orphan*/  ixgbe_read_iosf_sb_reg_x550 ; 
 int /*<<< orphan*/  ixgbe_read_iosf_sb_reg_x550a ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync_X550a ; 
 int /*<<< orphan*/  ixgbe_setup_eee_fw ; 
 int /*<<< orphan*/ * ixgbe_setup_fc_backplane_x550em_a ; 
 int /*<<< orphan*/  ixgbe_write_iosf_sb_reg_x550 ; 
 int /*<<< orphan*/  ixgbe_write_iosf_sb_reg_x550a ; 
 int stub1 (struct ixgbe_hw*) ; 

s32 ixgbe_init_ops_X550EM_a(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	s32 ret_val;

	DEBUGFUNC("ixgbe_init_ops_X550EM_a");

	/* Start with generic X550EM init */
	ret_val = ixgbe_init_ops_X550EM(hw);

	if (hw->device_id == IXGBE_DEV_ID_X550EM_A_SGMII ||
	    hw->device_id == IXGBE_DEV_ID_X550EM_A_SGMII_L) {
		mac->ops.read_iosf_sb_reg = ixgbe_read_iosf_sb_reg_x550;
		mac->ops.write_iosf_sb_reg = ixgbe_write_iosf_sb_reg_x550;
	} else {
		mac->ops.read_iosf_sb_reg = ixgbe_read_iosf_sb_reg_x550a;
		mac->ops.write_iosf_sb_reg = ixgbe_write_iosf_sb_reg_x550a;
	}
	mac->ops.acquire_swfw_sync = ixgbe_acquire_swfw_sync_X550a;
	mac->ops.release_swfw_sync = ixgbe_release_swfw_sync_X550a;

	switch (mac->ops.get_media_type(hw)) {
	case ixgbe_media_type_fiber:
		mac->ops.setup_fc = NULL;
		mac->ops.fc_autoneg = ixgbe_fc_autoneg_fiber_x550em_a;
		break;
	case ixgbe_media_type_backplane:
		mac->ops.fc_autoneg = ixgbe_fc_autoneg_backplane_x550em_a;
		mac->ops.setup_fc = ixgbe_setup_fc_backplane_x550em_a;
		break;
	default:
		break;
	}

	switch (hw->device_id) {
	case IXGBE_DEV_ID_X550EM_A_1G_T:
	case IXGBE_DEV_ID_X550EM_A_1G_T_L:
		mac->ops.fc_autoneg = ixgbe_fc_autoneg_sgmii_x550em_a;
		mac->ops.setup_fc = ixgbe_fc_autoneg_fw;
		mac->ops.setup_eee = ixgbe_setup_eee_fw;
		hw->phy.eee_speeds_supported = IXGBE_LINK_SPEED_100_FULL |
					       IXGBE_LINK_SPEED_1GB_FULL;
		hw->phy.eee_speeds_advertised = hw->phy.eee_speeds_supported;
		break;
	default:
		break;
	}

	return ret_val;
}