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
struct TYPE_4__ {int /*<<< orphan*/  clear_hw_cntrs; int /*<<< orphan*/  led_off; int /*<<< orphan*/  led_on; int /*<<< orphan*/  cleanup_led; int /*<<< orphan*/  setup_led; int /*<<< orphan*/  id_led_init; int /*<<< orphan*/  read_mac_addr; int /*<<< orphan*/  clear_vfta; int /*<<< orphan*/  write_vfta; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/  get_link_up_info; int /*<<< orphan*/  check_for_link; int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  set_lan_id; int /*<<< orphan*/  get_bus_info; } ;
struct e1000_mac_info {int mta_reg_count; TYPE_2__ ops; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_3__ {int media_type; } ;
struct e1000_hw {int device_id; TYPE_1__ phy; struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
#define  E1000_DEV_ID_82545EM_FIBER 136 
#define  E1000_DEV_ID_82545GM_FIBER 135 
#define  E1000_DEV_ID_82545GM_SERDES 134 
#define  E1000_DEV_ID_82546EB_FIBER 133 
#define  E1000_DEV_ID_82546GB_FIBER 132 
#define  E1000_DEV_ID_82546GB_SERDES 131 
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_check_for_copper_link_generic ; 
 int /*<<< orphan*/  e1000_check_for_fiber_link_generic ; 
 int /*<<< orphan*/  e1000_check_for_serdes_link_generic ; 
 int /*<<< orphan*/  e1000_cleanup_led_generic ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_82540 ; 
 int /*<<< orphan*/  e1000_clear_vfta_generic ; 
 int /*<<< orphan*/  e1000_get_bus_info_pci_generic ; 
 int /*<<< orphan*/  e1000_get_speed_and_duplex_copper_generic ; 
 int /*<<< orphan*/  e1000_get_speed_and_duplex_fiber_serdes_generic ; 
 int /*<<< orphan*/  e1000_id_led_init_generic ; 
 int /*<<< orphan*/  e1000_init_hw_82540 ; 
 int /*<<< orphan*/  e1000_led_off_generic ; 
 int /*<<< orphan*/  e1000_led_on_generic ; 
#define  e1000_media_type_copper 130 
#define  e1000_media_type_fiber 129 
#define  e1000_media_type_internal_serdes 128 
 int /*<<< orphan*/  e1000_read_mac_addr_82540 ; 
 int /*<<< orphan*/  e1000_reset_hw_82540 ; 
 int /*<<< orphan*/  e1000_set_lan_id_multi_port_pci ; 
 int /*<<< orphan*/  e1000_setup_copper_link_82540 ; 
 int /*<<< orphan*/  e1000_setup_fiber_serdes_link_82540 ; 
 int /*<<< orphan*/  e1000_setup_led_generic ; 
 int /*<<< orphan*/  e1000_setup_link_generic ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_generic ; 
 int /*<<< orphan*/  e1000_write_vfta_generic ; 

__attribute__((used)) static s32 e1000_init_mac_params_82540(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_init_mac_params_82540");

	/* Set media type */
	switch (hw->device_id) {
	case E1000_DEV_ID_82545EM_FIBER:
	case E1000_DEV_ID_82545GM_FIBER:
	case E1000_DEV_ID_82546EB_FIBER:
	case E1000_DEV_ID_82546GB_FIBER:
		hw->phy.media_type = e1000_media_type_fiber;
		break;
	case E1000_DEV_ID_82545GM_SERDES:
	case E1000_DEV_ID_82546GB_SERDES:
		hw->phy.media_type = e1000_media_type_internal_serdes;
		break;
	default:
		hw->phy.media_type = e1000_media_type_copper;
		break;
	}

	/* Set mta register count */
	mac->mta_reg_count = 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES;

	/* Function pointers */

	/* bus type/speed/width */
	mac->ops.get_bus_info = e1000_get_bus_info_pci_generic;
	/* function id */
	mac->ops.set_lan_id = e1000_set_lan_id_multi_port_pci;
	/* reset */
	mac->ops.reset_hw = e1000_reset_hw_82540;
	/* hw initialization */
	mac->ops.init_hw = e1000_init_hw_82540;
	/* link setup */
	mac->ops.setup_link = e1000_setup_link_generic;
	/* physical interface setup */
	mac->ops.setup_physical_interface =
		(hw->phy.media_type == e1000_media_type_copper)
			? e1000_setup_copper_link_82540
			: e1000_setup_fiber_serdes_link_82540;
	/* check for link */
	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		mac->ops.check_for_link = e1000_check_for_copper_link_generic;
		break;
	case e1000_media_type_fiber:
		mac->ops.check_for_link = e1000_check_for_fiber_link_generic;
		break;
	case e1000_media_type_internal_serdes:
		mac->ops.check_for_link = e1000_check_for_serdes_link_generic;
		break;
	default:
		ret_val = -E1000_ERR_CONFIG;
		goto out;
		break;
	}
	/* link info */
	mac->ops.get_link_up_info =
		(hw->phy.media_type == e1000_media_type_copper)
			? e1000_get_speed_and_duplex_copper_generic
			: e1000_get_speed_and_duplex_fiber_serdes_generic;
	/* multicast address update */
	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_generic;
	/* writing VFTA */
	mac->ops.write_vfta = e1000_write_vfta_generic;
	/* clearing VFTA */
	mac->ops.clear_vfta = e1000_clear_vfta_generic;
	/* read mac address */
	mac->ops.read_mac_addr = e1000_read_mac_addr_82540;
	/* ID LED init */
	mac->ops.id_led_init = e1000_id_led_init_generic;
	/* setup LED */
	mac->ops.setup_led = e1000_setup_led_generic;
	/* cleanup LED */
	mac->ops.cleanup_led = e1000_cleanup_led_generic;
	/* turn on/off LED */
	mac->ops.led_on = e1000_led_on_generic;
	mac->ops.led_off = e1000_led_off_generic;
	/* clear hardware counters */
	mac->ops.clear_hw_cntrs = e1000_clear_hw_cntrs_82540;

out:
	return ret_val;
}