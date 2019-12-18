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
struct TYPE_4__ {int /*<<< orphan*/  set_obff_timer; int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  rar_set; int /*<<< orphan*/  led_off; int /*<<< orphan*/  led_on; int /*<<< orphan*/  cleanup_led; int /*<<< orphan*/  setup_led; int /*<<< orphan*/  id_led_init; int /*<<< orphan*/  check_mng_mode; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/  blink_led; int /*<<< orphan*/  clear_hw_cntrs; int /*<<< orphan*/  get_link_up_info; int /*<<< orphan*/  check_for_link; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  set_lan_id; int /*<<< orphan*/  get_bus_info; } ;
struct e1000_mac_info {int mta_reg_count; int type; TYPE_2__ ops; scalar_t__ rar_entry_count; void* adaptive_ifs; int /*<<< orphan*/  arc_subsystem_valid; void* has_fwsm; void* asf_firmware_present; } ;
struct TYPE_3__ {int /*<<< orphan*/  media_type; } ;
struct e1000_hw {TYPE_1__ phy; struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ E1000_ICH_RAR_ENTRIES ; 
 scalar_t__ E1000_PCH2_RAR_ENTRIES ; 
 scalar_t__ E1000_PCH_LPT_RAR_ENTRIES ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  e1000_blink_led_generic ; 
 int /*<<< orphan*/  e1000_check_for_copper_link_ich8lan ; 
 int /*<<< orphan*/  e1000_check_mng_mode_ich8lan ; 
 int /*<<< orphan*/  e1000_check_mng_mode_pchlan ; 
 int /*<<< orphan*/  e1000_cleanup_led_ich8lan ; 
 int /*<<< orphan*/  e1000_cleanup_led_pchlan ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_ich8lan ; 
 int /*<<< orphan*/  e1000_get_bus_info_ich8lan ; 
 int /*<<< orphan*/  e1000_get_link_up_info_ich8lan ; 
#define  e1000_ich10lan 135 
#define  e1000_ich8lan 134 
#define  e1000_ich9lan 133 
 int /*<<< orphan*/  e1000_id_led_init_generic ; 
 int /*<<< orphan*/  e1000_id_led_init_pchlan ; 
 int /*<<< orphan*/  e1000_init_hw_ich8lan ; 
 int /*<<< orphan*/  e1000_led_off_ich8lan ; 
 int /*<<< orphan*/  e1000_led_off_pchlan ; 
 int /*<<< orphan*/  e1000_led_on_ich8lan ; 
 int /*<<< orphan*/  e1000_led_on_pchlan ; 
 int /*<<< orphan*/  e1000_media_type_copper ; 
#define  e1000_pch2lan 132 
#define  e1000_pch_cnp 131 
#define  e1000_pch_lpt 130 
#define  e1000_pch_spt 129 
#define  e1000_pchlan 128 
 int /*<<< orphan*/  e1000_rar_set_pch2lan ; 
 int /*<<< orphan*/  e1000_rar_set_pch_lpt ; 
 int /*<<< orphan*/  e1000_reset_hw_ich8lan ; 
 int /*<<< orphan*/  e1000_set_kmrn_lock_loss_workaround_ich8lan (struct e1000_hw*,void*) ; 
 int /*<<< orphan*/  e1000_set_lan_id_single_port ; 
 int /*<<< orphan*/  e1000_set_obff_timer_pch_lpt ; 
 int /*<<< orphan*/  e1000_setup_copper_link_ich8lan ; 
 int /*<<< orphan*/  e1000_setup_copper_link_pch_lpt ; 
 int /*<<< orphan*/  e1000_setup_led_generic ; 
 int /*<<< orphan*/  e1000_setup_led_pchlan ; 
 int /*<<< orphan*/  e1000_setup_link_ich8lan ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_generic ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_pch2lan ; 

__attribute__((used)) static s32 e1000_init_mac_params_ich8lan(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;

	DEBUGFUNC("e1000_init_mac_params_ich8lan");

	/* Set media type function pointer */
	hw->phy.media_type = e1000_media_type_copper;

	/* Set mta register count */
	mac->mta_reg_count = 32;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_ICH_RAR_ENTRIES;
	if (mac->type == e1000_ich8lan)
		mac->rar_entry_count--;
	/* Set if part includes ASF firmware */
	mac->asf_firmware_present = TRUE;
	/* FWSM register */
	mac->has_fwsm = TRUE;
	/* ARC subsystem not supported */
	mac->arc_subsystem_valid = FALSE;
	/* Adaptive IFS supported */
	mac->adaptive_ifs = TRUE;

	/* Function pointers */

	/* bus type/speed/width */
	mac->ops.get_bus_info = e1000_get_bus_info_ich8lan;
	/* function id */
	mac->ops.set_lan_id = e1000_set_lan_id_single_port;
	/* reset */
	mac->ops.reset_hw = e1000_reset_hw_ich8lan;
	/* hw initialization */
	mac->ops.init_hw = e1000_init_hw_ich8lan;
	/* link setup */
	mac->ops.setup_link = e1000_setup_link_ich8lan;
	/* physical interface setup */
	mac->ops.setup_physical_interface = e1000_setup_copper_link_ich8lan;
	/* check for link */
	mac->ops.check_for_link = e1000_check_for_copper_link_ich8lan;
	/* link info */
	mac->ops.get_link_up_info = e1000_get_link_up_info_ich8lan;
	/* multicast address update */
	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_generic;
	/* clear hardware counters */
	mac->ops.clear_hw_cntrs = e1000_clear_hw_cntrs_ich8lan;

	/* LED and other operations */
	switch (mac->type) {
	case e1000_ich8lan:
	case e1000_ich9lan:
	case e1000_ich10lan:
		/* check management mode */
		mac->ops.check_mng_mode = e1000_check_mng_mode_ich8lan;
		/* ID LED init */
		mac->ops.id_led_init = e1000_id_led_init_generic;
		/* blink LED */
		mac->ops.blink_led = e1000_blink_led_generic;
		/* setup LED */
		mac->ops.setup_led = e1000_setup_led_generic;
		/* cleanup LED */
		mac->ops.cleanup_led = e1000_cleanup_led_ich8lan;
		/* turn on/off LED */
		mac->ops.led_on = e1000_led_on_ich8lan;
		mac->ops.led_off = e1000_led_off_ich8lan;
		break;
	case e1000_pch2lan:
		mac->rar_entry_count = E1000_PCH2_RAR_ENTRIES;
		mac->ops.rar_set = e1000_rar_set_pch2lan;
		/* fall-through */
	case e1000_pch_lpt:
	case e1000_pch_spt:
	case e1000_pch_cnp:
		/* multicast address update for pch2 */
		mac->ops.update_mc_addr_list =
			e1000_update_mc_addr_list_pch2lan;
		/* fall-through */
	case e1000_pchlan:
		/* check management mode */
		mac->ops.check_mng_mode = e1000_check_mng_mode_pchlan;
		/* ID LED init */
		mac->ops.id_led_init = e1000_id_led_init_pchlan;
		/* setup LED */
		mac->ops.setup_led = e1000_setup_led_pchlan;
		/* cleanup LED */
		mac->ops.cleanup_led = e1000_cleanup_led_pchlan;
		/* turn on/off LED */
		mac->ops.led_on = e1000_led_on_pchlan;
		mac->ops.led_off = e1000_led_off_pchlan;
		break;
	default:
		break;
	}

	if (mac->type >= e1000_pch_lpt) {
		mac->rar_entry_count = E1000_PCH_LPT_RAR_ENTRIES;
		mac->ops.rar_set = e1000_rar_set_pch_lpt;
		mac->ops.setup_physical_interface = e1000_setup_copper_link_pch_lpt;
		mac->ops.set_obff_timer = e1000_set_obff_timer_pch_lpt;
	}

	/* Enable PCS Lock-loss workaround for ICH8 */
	if (mac->type == e1000_ich8lan)
		e1000_set_kmrn_lock_loss_workaround_ich8lan(hw, TRUE);

	return E1000_SUCCESS;
}