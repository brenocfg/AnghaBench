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
typedef  int u32 ;
struct TYPE_6__ {void* blink_led; void* led_on; void* check_mng_mode; void* set_lan_id; int /*<<< orphan*/  clear_hw_cntrs; int /*<<< orphan*/  led_off; int /*<<< orphan*/  cleanup_led; int /*<<< orphan*/  setup_led; int /*<<< orphan*/  id_led_init; int /*<<< orphan*/  read_mac_addr; int /*<<< orphan*/  clear_vfta; int /*<<< orphan*/  write_vfta; int /*<<< orphan*/  update_mc_addr_list; int /*<<< orphan*/  setup_link; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  reset_hw; int /*<<< orphan*/  get_bus_info; void* get_link_up_info; int /*<<< orphan*/  check_for_link; void* setup_physical_interface; } ;
struct e1000_mac_info {int mta_reg_count; int type; int arc_subsystem_valid; void* has_fwsm; TYPE_2__ ops; void* adaptive_ifs; void* asf_firmware_present; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_7__ {scalar_t__ smb_counter; } ;
struct TYPE_8__ {TYPE_3__ _82571; } ;
struct TYPE_5__ {int /*<<< orphan*/  media_type; } ;
struct e1000_hw {int device_id; TYPE_4__ dev_spec; struct e1000_mac_info mac; TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
#define  E1000_DEV_ID_82571EB_FIBER 139 
#define  E1000_DEV_ID_82571EB_QUAD_FIBER 138 
#define  E1000_DEV_ID_82571EB_SERDES 137 
#define  E1000_DEV_ID_82571EB_SERDES_DUAL 136 
#define  E1000_DEV_ID_82571EB_SERDES_QUAD 135 
#define  E1000_DEV_ID_82572EI_FIBER 134 
#define  E1000_DEV_ID_82572EI_SERDES 133 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_FWSM_MODE_MASK ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_SWSM ; 
 int /*<<< orphan*/  E1000_SWSM2 ; 
 int E1000_SWSM2_LOCK ; 
 int E1000_SWSM_SMBI ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 void* TRUE ; 
#define  e1000_82571 132 
#define  e1000_82572 131 
#define  e1000_82573 130 
#define  e1000_82574 129 
#define  e1000_82583 128 
 void* e1000_blink_led_generic ; 
 int /*<<< orphan*/  e1000_check_for_copper_link_generic ; 
 int /*<<< orphan*/  e1000_check_for_fiber_link_generic ; 
 int /*<<< orphan*/  e1000_check_for_serdes_link_82571 ; 
 void* e1000_check_mng_mode_82574 ; 
 void* e1000_check_mng_mode_generic ; 
 int /*<<< orphan*/  e1000_cleanup_led_generic ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_82571 ; 
 int /*<<< orphan*/  e1000_clear_vfta_82571 ; 
 int /*<<< orphan*/  e1000_get_bus_info_pcie_generic ; 
 void* e1000_get_speed_and_duplex_copper_generic ; 
 void* e1000_get_speed_and_duplex_fiber_serdes_generic ; 
 int /*<<< orphan*/  e1000_id_led_init_generic ; 
 int /*<<< orphan*/  e1000_init_hw_82571 ; 
 int /*<<< orphan*/  e1000_led_off_generic ; 
 void* e1000_led_on_82574 ; 
 void* e1000_led_on_generic ; 
 int /*<<< orphan*/  e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_media_type_fiber ; 
 int /*<<< orphan*/  e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  e1000_read_mac_addr_82571 ; 
 int /*<<< orphan*/  e1000_reset_hw_82571 ; 
 void* e1000_set_lan_id_single_port ; 
 void* e1000_setup_copper_link_82571 ; 
 void* e1000_setup_fiber_serdes_link_82571 ; 
 int /*<<< orphan*/  e1000_setup_led_generic ; 
 int /*<<< orphan*/  e1000_setup_link_82571 ; 
 int /*<<< orphan*/  e1000_update_mc_addr_list_generic ; 
 int /*<<< orphan*/  e1000_write_vfta_generic ; 

__attribute__((used)) static s32 e1000_init_mac_params_82571(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 swsm = 0;
	u32 swsm2 = 0;
	bool force_clear_smbi = FALSE;

	DEBUGFUNC("e1000_init_mac_params_82571");

	/* Set media type and media-dependent function pointers */
	switch (hw->device_id) {
	case E1000_DEV_ID_82571EB_FIBER:
	case E1000_DEV_ID_82572EI_FIBER:
	case E1000_DEV_ID_82571EB_QUAD_FIBER:
		hw->phy.media_type = e1000_media_type_fiber;
		mac->ops.setup_physical_interface =
			e1000_setup_fiber_serdes_link_82571;
		mac->ops.check_for_link = e1000_check_for_fiber_link_generic;
		mac->ops.get_link_up_info =
			e1000_get_speed_and_duplex_fiber_serdes_generic;
		break;
	case E1000_DEV_ID_82571EB_SERDES:
	case E1000_DEV_ID_82571EB_SERDES_DUAL:
	case E1000_DEV_ID_82571EB_SERDES_QUAD:
	case E1000_DEV_ID_82572EI_SERDES:
		hw->phy.media_type = e1000_media_type_internal_serdes;
		mac->ops.setup_physical_interface =
			e1000_setup_fiber_serdes_link_82571;
		mac->ops.check_for_link = e1000_check_for_serdes_link_82571;
		mac->ops.get_link_up_info =
			e1000_get_speed_and_duplex_fiber_serdes_generic;
		break;
	default:
		hw->phy.media_type = e1000_media_type_copper;
		mac->ops.setup_physical_interface =
			e1000_setup_copper_link_82571;
		mac->ops.check_for_link = e1000_check_for_copper_link_generic;
		mac->ops.get_link_up_info =
			e1000_get_speed_and_duplex_copper_generic;
		break;
	}

	/* Set mta register count */
	mac->mta_reg_count = 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES;
	/* Set if part includes ASF firmware */
	mac->asf_firmware_present = TRUE;
	/* Adaptive IFS supported */
	mac->adaptive_ifs = TRUE;

	/* Function pointers */

	/* bus type/speed/width */
	mac->ops.get_bus_info = e1000_get_bus_info_pcie_generic;
	/* reset */
	mac->ops.reset_hw = e1000_reset_hw_82571;
	/* hw initialization */
	mac->ops.init_hw = e1000_init_hw_82571;
	/* link setup */
	mac->ops.setup_link = e1000_setup_link_82571;
	/* multicast address update */
	mac->ops.update_mc_addr_list = e1000_update_mc_addr_list_generic;
	/* writing VFTA */
	mac->ops.write_vfta = e1000_write_vfta_generic;
	/* clearing VFTA */
	mac->ops.clear_vfta = e1000_clear_vfta_82571;
	/* read mac address */
	mac->ops.read_mac_addr = e1000_read_mac_addr_82571;
	/* ID LED init */
	mac->ops.id_led_init = e1000_id_led_init_generic;
	/* setup LED */
	mac->ops.setup_led = e1000_setup_led_generic;
	/* cleanup LED */
	mac->ops.cleanup_led = e1000_cleanup_led_generic;
	/* turn off LED */
	mac->ops.led_off = e1000_led_off_generic;
	/* clear hardware counters */
	mac->ops.clear_hw_cntrs = e1000_clear_hw_cntrs_82571;

	/* MAC-specific function pointers */
	switch (hw->mac.type) {
	case e1000_82573:
		mac->ops.set_lan_id = e1000_set_lan_id_single_port;
		mac->ops.check_mng_mode = e1000_check_mng_mode_generic;
		mac->ops.led_on = e1000_led_on_generic;
		mac->ops.blink_led = e1000_blink_led_generic;

		/* FWSM register */
		mac->has_fwsm = TRUE;
		/* ARC supported; valid only if manageability features are
		 * enabled.
		 */
		mac->arc_subsystem_valid = !!(E1000_READ_REG(hw, E1000_FWSM) &
					      E1000_FWSM_MODE_MASK);
		break;
	case e1000_82574:
	case e1000_82583:
		mac->ops.set_lan_id = e1000_set_lan_id_single_port;
		mac->ops.check_mng_mode = e1000_check_mng_mode_82574;
		mac->ops.led_on = e1000_led_on_82574;
		break;
	default:
		mac->ops.check_mng_mode = e1000_check_mng_mode_generic;
		mac->ops.led_on = e1000_led_on_generic;
		mac->ops.blink_led = e1000_blink_led_generic;

		/* FWSM register */
		mac->has_fwsm = TRUE;
		break;
	}

	/* Ensure that the inter-port SWSM.SMBI lock bit is clear before
	 * first NVM or PHY access. This should be done for single-port
	 * devices, and for one port only on dual-port devices so that
	 * for those devices we can still use the SMBI lock to synchronize
	 * inter-port accesses to the PHY & NVM.
	 */
	switch (hw->mac.type) {
	case e1000_82571:
	case e1000_82572:
		swsm2 = E1000_READ_REG(hw, E1000_SWSM2);

		if (!(swsm2 & E1000_SWSM2_LOCK)) {
			/* Only do this for the first interface on this card */
			E1000_WRITE_REG(hw, E1000_SWSM2, swsm2 |
					E1000_SWSM2_LOCK);
			force_clear_smbi = TRUE;
		} else {
			force_clear_smbi = FALSE;
		}
		break;
	default:
		force_clear_smbi = TRUE;
		break;
	}

	if (force_clear_smbi) {
		/* Make sure SWSM.SMBI is clear */
		swsm = E1000_READ_REG(hw, E1000_SWSM);
		if (swsm & E1000_SWSM_SMBI) {
			/* This bit should not be set on a first interface, and
			 * indicates that the bootagent or EFI code has
			 * improperly left this bit enabled
			 */
			DEBUGOUT("Please update your 82571 Bootagent\n");
		}
		E1000_WRITE_REG(hw, E1000_SWSM, swsm & ~E1000_SWSM_SMBI);
	}

	/* Initialze device specific counter of SMBI acquisition timeouts. */
	 hw->dev_spec._82571.smb_counter = 0;

	return E1000_SUCCESS;
}