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
struct TYPE_4__ {int /*<<< orphan*/  (* set_lan_id ) (struct e1000_hw*) ;int /*<<< orphan*/  get_link_up_info; int /*<<< orphan*/  clear_hw_cntrs; int /*<<< orphan*/  led_off; int /*<<< orphan*/  led_on; int /*<<< orphan*/  cleanup_led; int /*<<< orphan*/  setup_led; int /*<<< orphan*/  blink_led; int /*<<< orphan*/  id_led_init; int /*<<< orphan*/  read_mac_addr; int /*<<< orphan*/  clear_vfta; int /*<<< orphan*/  write_vfta; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/  check_mng_mode; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  get_bus_info; int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  check_for_link; } ;
struct e1000_mac_info {int mta_reg_count; int arc_subsystem_valid; TYPE_2__ ops; int /*<<< orphan*/  adaptive_ifs; void* has_fwsm; void* asf_firmware_present; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  media_type; } ;
struct e1000_hw {int device_id; struct e1000_mac_info mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
#define  E1000_DEV_ID_80003ES2LAN_SERDES_DPT 128 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_FWSM_MODE_MASK ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  e1000_blink_led_generic ; 
 int /*<<< orphan*/  e1000_check_for_copper_link_generic ; 
 int /*<<< orphan*/  e1000_check_for_serdes_link_generic ; 
 int /*<<< orphan*/  e1000_check_mng_mode_generic ; 
 int /*<<< orphan*/  e1000_cleanup_led_generic ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_80003es2lan ; 
 int /*<<< orphan*/  e1000_clear_vfta_generic ; 
 int /*<<< orphan*/  e1000_get_bus_info_pcie_generic ; 
 int /*<<< orphan*/  e1000_get_link_up_info_80003es2lan ; 
 int /*<<< orphan*/  e1000_id_led_init_generic ; 
 int /*<<< orphan*/  e1000_init_hw_80003es2lan ; 
 int /*<<< orphan*/  e1000_led_off_generic ; 
 int /*<<< orphan*/  e1000_led_on_generic ; 
 int /*<<< orphan*/  e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  e1000_read_mac_addr_80003es2lan ; 
 int /*<<< orphan*/  e1000_reset_hw_80003es2lan ; 
 int /*<<< orphan*/  e1000_setup_copper_link_80003es2lan ; 
 int /*<<< orphan*/  e1000_setup_fiber_serdes_link_generic ; 
 int /*<<< orphan*/  e1000_setup_led_generic ; 
 int /*<<< orphan*/  e1000_setup_link_generic ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_generic ; 
 int /*<<< orphan*/  e1000_write_vfta_generic ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_init_mac_params_80003es2lan(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	DEBUGFUNC("e1000_init_mac_params_80003es2lan");

	/* Set media type and media-dependent function pointers */
	switch (hw->device_id) {
	case E1000_DEV_ID_80003ES2LAN_SERDES_DPT:
		hw->phy.media_type = e1000_media_type_internal_serdes;
		mac->ops.check_for_link = e1000_check_for_serdes_link_generic;
		mac->ops.setup_physical_interface =
					e1000_setup_fiber_serdes_link_generic;
		break;
	default:
		hw->phy.media_type = e1000_media_type_copper;
		mac->ops.check_for_link = e1000_check_for_copper_link_generic;
		mac->ops.setup_physical_interface =
					e1000_setup_copper_link_80003es2lan;
		break;
	}

	/* Set mta register count */
	mac->mta_reg_count = 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES;
	/* Set if part includes ASF firmware */
	mac->asf_firmware_present = TRUE;
	/* FWSM register */
	mac->has_fwsm = TRUE;
	/* ARC supported; valid only if manageability features are enabled. */
	mac->arc_subsystem_valid = !!(E1000_READ_REG(hw, E1000_FWSM) &
				      E1000_FWSM_MODE_MASK);
	/* Adaptive IFS not supported */
	mac->adaptive_ifs = FALSE;

	/* Function pointers */

	/* bus type/speed/width */
	mac->ops.get_bus_info = e1000_get_bus_info_pcie_generic;
	/* reset */
	mac->ops.reset_hw = e1000_reset_hw_80003es2lan;
	/* hw initialization */
	mac->ops.init_hw = e1000_init_hw_80003es2lan;
	/* link setup */
	mac->ops.setup_link = e1000_setup_link_generic;
	/* check management mode */
	mac->ops.check_mng_mode = e1000_check_mng_mode_generic;
	/* multicast address update */
	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_generic;
	/* writing VFTA */
	mac->ops.write_vfta = e1000_write_vfta_generic;
	/* clearing VFTA */
	mac->ops.clear_vfta = e1000_clear_vfta_generic;
	/* read mac address */
	mac->ops.read_mac_addr = e1000_read_mac_addr_80003es2lan;
	/* ID LED init */
	mac->ops.id_led_init = e1000_id_led_init_generic;
	/* blink LED */
	mac->ops.blink_led = e1000_blink_led_generic;
	/* setup LED */
	mac->ops.setup_led = e1000_setup_led_generic;
	/* cleanup LED */
	mac->ops.cleanup_led = e1000_cleanup_led_generic;
	/* turn on/off LED */
	mac->ops.led_on = e1000_led_on_generic;
	mac->ops.led_off = e1000_led_off_generic;
	/* clear hardware counters */
	mac->ops.clear_hw_cntrs = e1000_clear_hw_cntrs_80003es2lan;
	/* link info */
	mac->ops.get_link_up_info = e1000_get_link_up_info_80003es2lan;

	/* set lan id for port to determine which phy lock to use */
	hw->mac.ops.set_lan_id(hw);

	return E1000_SUCCESS;
}