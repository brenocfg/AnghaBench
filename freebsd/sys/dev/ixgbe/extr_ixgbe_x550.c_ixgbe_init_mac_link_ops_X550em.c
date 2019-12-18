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
struct TYPE_2__ {int (* get_media_type ) (struct ixgbe_hw*) ;void* setup_link; int /*<<< orphan*/  check_link; int /*<<< orphan*/  setup_mac_link; int /*<<< orphan*/  set_rate_select_speed; int /*<<< orphan*/ * flap_tx_laser; int /*<<< orphan*/ * enable_tx_laser; int /*<<< orphan*/ * disable_tx_laser; } ;
struct ixgbe_mac_info {TYPE_1__ ops; int /*<<< orphan*/  type; } ;
struct ixgbe_hw {int /*<<< orphan*/  device_id; struct ixgbe_mac_info mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_1G_T ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_1G_T_L ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SFP ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SFP_N ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SGMII ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SGMII_L ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_X_1G_T ; 
 int /*<<< orphan*/  ixgbe_check_link_t_X550em ; 
 int /*<<< orphan*/  ixgbe_check_mac_link_generic ; 
 int /*<<< orphan*/  ixgbe_mac_X550EM_a ; 
#define  ixgbe_media_type_backplane 130 
#define  ixgbe_media_type_copper 129 
#define  ixgbe_media_type_fiber 128 
 int /*<<< orphan*/  ixgbe_set_soft_rate_select_speed ; 
 void* ixgbe_setup_mac_link_multispeed_fiber ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_sfp_x550a ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_sfp_x550em ; 
 void* ixgbe_setup_mac_link_t_X550em ; 
 void* ixgbe_setup_sgmii ; 
 void* ixgbe_setup_sgmii_fw ; 
 int stub1 (struct ixgbe_hw*) ; 

void ixgbe_init_mac_link_ops_X550em(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;

	DEBUGFUNC("ixgbe_init_mac_link_ops_X550em");

	switch (hw->mac.ops.get_media_type(hw)) {
	case ixgbe_media_type_fiber:
		/* CS4227 does not support autoneg, so disable the laser control
		 * functions for SFP+ fiber
		 */
		mac->ops.disable_tx_laser = NULL;
		mac->ops.enable_tx_laser = NULL;
		mac->ops.flap_tx_laser = NULL;
		mac->ops.setup_link = ixgbe_setup_mac_link_multispeed_fiber;
		mac->ops.set_rate_select_speed =
					ixgbe_set_soft_rate_select_speed;

		if ((hw->device_id == IXGBE_DEV_ID_X550EM_A_SFP_N) ||
		    (hw->device_id == IXGBE_DEV_ID_X550EM_A_SFP))
			mac->ops.setup_mac_link =
						ixgbe_setup_mac_link_sfp_x550a;
		else
			mac->ops.setup_mac_link =
						ixgbe_setup_mac_link_sfp_x550em;
		break;
	case ixgbe_media_type_copper:
		if (hw->device_id == IXGBE_DEV_ID_X550EM_X_1G_T)
			break;
		if (hw->mac.type == ixgbe_mac_X550EM_a) {
			if (hw->device_id == IXGBE_DEV_ID_X550EM_A_1G_T ||
			    hw->device_id == IXGBE_DEV_ID_X550EM_A_1G_T_L) {
				mac->ops.setup_link = ixgbe_setup_sgmii_fw;
				mac->ops.check_link =
						   ixgbe_check_mac_link_generic;
			} else {
				mac->ops.setup_link =
						  ixgbe_setup_mac_link_t_X550em;
			}
		} else {
			mac->ops.setup_link = ixgbe_setup_mac_link_t_X550em;
			mac->ops.check_link = ixgbe_check_link_t_X550em;
		}
		break;
	case ixgbe_media_type_backplane:
		if (hw->device_id == IXGBE_DEV_ID_X550EM_A_SGMII ||
		    hw->device_id == IXGBE_DEV_ID_X550EM_A_SGMII_L)
			mac->ops.setup_link = ixgbe_setup_sgmii;
		break;
	default:
		break;
	}
}