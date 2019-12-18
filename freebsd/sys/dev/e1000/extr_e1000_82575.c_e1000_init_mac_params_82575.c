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
struct TYPE_6__ {int /*<<< orphan*/  (* set_lan_id ) (struct e1000_hw*) ;int /*<<< orphan*/  release_swfw_sync; int /*<<< orphan*/  acquire_swfw_sync; int /*<<< orphan*/  get_link_up_info; int /*<<< orphan*/  clear_hw_cntrs; int /*<<< orphan*/  led_off; int /*<<< orphan*/  led_on; int /*<<< orphan*/  cleanup_led; int /*<<< orphan*/  setup_led; int /*<<< orphan*/  blink_led; int /*<<< orphan*/  id_led_init; int /*<<< orphan*/  validate_mdi_setting; int /*<<< orphan*/  clear_vfta; int /*<<< orphan*/  write_vfta; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/  config_collision_dist; int /*<<< orphan*/  read_mac_addr; int /*<<< orphan*/  check_for_link; int /*<<< orphan*/  power_up_serdes; int /*<<< orphan*/  shutdown_serdes; int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  get_bus_info; } ;
struct e1000_mac_info {int mta_reg_count; int uta_reg_count; scalar_t__ type; int arc_subsystem_valid; TYPE_3__ ops; void* has_fwsm; void* asf_firmware_present; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_5__ {scalar_t__ media_type; } ;
struct e1000_dev_spec_82575 {void* clear_semaphore_once; int /*<<< orphan*/  eee_disable; } ;
struct TYPE_4__ {struct e1000_dev_spec_82575 _82575; } ;
struct e1000_hw {struct e1000_mac_info mac; TYPE_2__ phy; TYPE_1__ dev_spec; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_FWSM_MODE_MASK ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES_82575 ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES_82576 ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES_82580 ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES_I350 ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 void* TRUE ; 
 scalar_t__ e1000_82575 ; 
 scalar_t__ e1000_82576 ; 
 scalar_t__ e1000_82580 ; 
 int /*<<< orphan*/  e1000_acquire_swfw_sync ; 
 int /*<<< orphan*/  e1000_blink_led_generic ; 
 int /*<<< orphan*/  e1000_check_for_link_82575 ; 
 int /*<<< orphan*/  e1000_cleanup_led_generic ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_82575 ; 
 int /*<<< orphan*/  e1000_clear_vfta_generic ; 
 int /*<<< orphan*/  e1000_clear_vfta_i350 ; 
 int /*<<< orphan*/  e1000_config_collision_dist_82575 ; 
 int /*<<< orphan*/  e1000_get_bus_info_pcie_generic ; 
 int /*<<< orphan*/  e1000_get_link_up_info_82575 ; 
 int /*<<< orphan*/  e1000_get_media_type_82575 (struct e1000_hw*) ; 
 scalar_t__ e1000_i210 ; 
 scalar_t__ e1000_i211 ; 
 scalar_t__ e1000_i350 ; 
 scalar_t__ e1000_i354 ; 
 int /*<<< orphan*/  e1000_id_led_init_generic ; 
 int /*<<< orphan*/  e1000_init_hw_82575 ; 
 int /*<<< orphan*/  e1000_init_hw_i210 ; 
 int /*<<< orphan*/  e1000_led_off_generic ; 
 int /*<<< orphan*/  e1000_led_on_generic ; 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_power_up_serdes_link_82575 ; 
 int /*<<< orphan*/  e1000_read_mac_addr_82575 ; 
 int /*<<< orphan*/  e1000_release_swfw_sync ; 
 int /*<<< orphan*/  e1000_reset_hw_82575 ; 
 int /*<<< orphan*/  e1000_reset_hw_82580 ; 
 int /*<<< orphan*/  e1000_setup_copper_link_82575 ; 
 int /*<<< orphan*/  e1000_setup_led_generic ; 
 int /*<<< orphan*/  e1000_setup_link_generic ; 
 int /*<<< orphan*/  e1000_setup_serdes_link_82575 ; 
 int /*<<< orphan*/  e1000_shutdown_serdes_link_82575 ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_generic ; 
 int /*<<< orphan*/  e1000_validate_mdi_setting_crossover_generic ; 
 int /*<<< orphan*/  e1000_write_vfta_generic ; 
 int /*<<< orphan*/  e1000_write_vfta_i350 ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_init_mac_params_82575(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	struct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;

	DEBUGFUNC("e1000_init_mac_params_82575");

	/* Derives media type */
	e1000_get_media_type_82575(hw);
	/* Set mta register count */
	mac->mta_reg_count = 128;
	/* Set uta register count */
	mac->uta_reg_count = (hw->mac.type == e1000_82575) ? 0 : 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES_82575;
	if (mac->type == e1000_82576)
		mac->rar_entry_count = E1000_RAR_ENTRIES_82576;
	if (mac->type == e1000_82580)
		mac->rar_entry_count = E1000_RAR_ENTRIES_82580;
	if (mac->type == e1000_i350 || mac->type == e1000_i354)
		mac->rar_entry_count = E1000_RAR_ENTRIES_I350;

	/* Enable EEE default settings for EEE supported devices */
	if (mac->type >= e1000_i350)
		dev_spec->eee_disable = FALSE;

	/* Allow a single clear of the SW semaphore on I210 and newer */
	if (mac->type >= e1000_i210)
		dev_spec->clear_semaphore_once = TRUE;

	/* Set if part includes ASF firmware */
	mac->asf_firmware_present = TRUE;
	/* FWSM register */
	mac->has_fwsm = TRUE;
	/* ARC supported; valid only if manageability features are enabled. */
	mac->arc_subsystem_valid =
		!!(E1000_READ_REG(hw, E1000_FWSM) & E1000_FWSM_MODE_MASK);

	/* Function pointers */

	/* bus type/speed/width */
	mac->ops.get_bus_info = e1000_get_bus_info_pcie_generic;
	/* reset */
	if (mac->type >= e1000_82580)
		mac->ops.reset_hw = e1000_reset_hw_82580;
	else
	mac->ops.reset_hw = e1000_reset_hw_82575;
	/* hw initialization */
	if ((mac->type == e1000_i210) || (mac->type == e1000_i211))
		mac->ops.init_hw = e1000_init_hw_i210;
	else
	mac->ops.init_hw = e1000_init_hw_82575;
	/* link setup */
	mac->ops.setup_link = e1000_setup_link_generic;
	/* physical interface link setup */
	mac->ops.setup_physical_interface =
		(hw->phy.media_type == e1000_media_type_copper)
		? e1000_setup_copper_link_82575 : e1000_setup_serdes_link_82575;
	/* physical interface shutdown */
	mac->ops.shutdown_serdes = e1000_shutdown_serdes_link_82575;
	/* physical interface power up */
	mac->ops.power_up_serdes = e1000_power_up_serdes_link_82575;
	/* check for link */
	mac->ops.check_for_link = e1000_check_for_link_82575;
	/* read mac address */
	mac->ops.read_mac_addr = e1000_read_mac_addr_82575;
	/* configure collision distance */
	mac->ops.config_collision_dist = e1000_config_collision_dist_82575;
	/* multicast address update */
	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_generic;
	if (hw->mac.type == e1000_i350 || mac->type == e1000_i354) {
		/* writing VFTA */
		mac->ops.write_vfta = e1000_write_vfta_i350;
		/* clearing VFTA */
		mac->ops.clear_vfta = e1000_clear_vfta_i350;
	} else {
		/* writing VFTA */
		mac->ops.write_vfta = e1000_write_vfta_generic;
		/* clearing VFTA */
		mac->ops.clear_vfta = e1000_clear_vfta_generic;
	}
	if (hw->mac.type >= e1000_82580)
		mac->ops.validate_mdi_setting =
				e1000_validate_mdi_setting_crossover_generic;
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
	mac->ops.clear_hw_cntrs = e1000_clear_hw_cntrs_82575;
	/* link info */
	mac->ops.get_link_up_info = e1000_get_link_up_info_82575;
	/* acquire SW_FW sync */
	mac->ops.acquire_swfw_sync = e1000_acquire_swfw_sync;
	mac->ops.release_swfw_sync = e1000_release_swfw_sync;

	/* set lan id for port to determine which phy lock to use */
	hw->mac.ops.set_lan_id(hw);

	return E1000_SUCCESS;
}