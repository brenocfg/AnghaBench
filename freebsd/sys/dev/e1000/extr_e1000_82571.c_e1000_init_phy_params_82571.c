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
struct TYPE_3__ {int /*<<< orphan*/  set_d3_lplu_state; int /*<<< orphan*/  set_d0_lplu_state; void* release; void* acquire; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; void* get_cable_length; void* force_speed_duplex; void* commit; void* check_polarity; void* get_info; void* get_cfg_done; int /*<<< orphan*/  power_down; int /*<<< orphan*/  power_up; int /*<<< orphan*/  reset; int /*<<< orphan*/  check_reset_block; } ;
struct e1000_phy_info {scalar_t__ media_type; int addr; int reset_delay_us; int /*<<< orphan*/  id; TYPE_1__ ops; int /*<<< orphan*/  type; int /*<<< orphan*/  autoneg_mask; } ;
struct TYPE_4__ {int type; } ;
struct e1000_hw {TYPE_2__ mac; struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ADVERTISE_SPEED_DEFAULT ; 
 int /*<<< orphan*/  BME1000_E_PHY_ID_R2 ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_ERR_PHY ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  IGP01E1000_I_PHY_ID ; 
 int /*<<< orphan*/  M88E1111_I_PHY_ID ; 
#define  e1000_82571 132 
#define  e1000_82572 131 
#define  e1000_82573 130 
#define  e1000_82574 129 
#define  e1000_82583 128 
 void* e1000_check_polarity_igp ; 
 void* e1000_check_polarity_m88 ; 
 int /*<<< orphan*/  e1000_check_reset_block_generic ; 
 void* e1000_get_cable_length_igp_2 ; 
 void* e1000_get_cable_length_m88 ; 
 void* e1000_get_cfg_done_82571 ; 
 void* e1000_get_cfg_done_generic ; 
 void* e1000_get_hw_semaphore ; 
 void* e1000_get_hw_semaphore_82574 ; 
 scalar_t__ e1000_get_phy_id_82571 (struct e1000_hw*) ; 
 void* e1000_get_phy_info_igp ; 
 void* e1000_get_phy_info_m88 ; 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_phy_bm ; 
 void* e1000_phy_force_speed_duplex_igp ; 
 void* e1000_phy_force_speed_duplex_m88 ; 
 int /*<<< orphan*/  e1000_phy_hw_reset_generic ; 
 int /*<<< orphan*/  e1000_phy_igp_2 ; 
 int /*<<< orphan*/  e1000_phy_m88 ; 
 int /*<<< orphan*/  e1000_phy_none ; 
 void* e1000_phy_sw_reset_generic ; 
 int /*<<< orphan*/  e1000_power_down_phy_copper_82571 ; 
 int /*<<< orphan*/  e1000_power_up_phy_copper ; 
 void* e1000_put_hw_semaphore ; 
 void* e1000_put_hw_semaphore_82574 ; 
 int /*<<< orphan*/  e1000_read_phy_reg_bm2 ; 
 int /*<<< orphan*/  e1000_read_phy_reg_igp ; 
 int /*<<< orphan*/  e1000_read_phy_reg_m88 ; 
 int /*<<< orphan*/  e1000_set_d0_lplu_state_82571 ; 
 int /*<<< orphan*/  e1000_set_d0_lplu_state_82574 ; 
 int /*<<< orphan*/  e1000_set_d3_lplu_state_82574 ; 
 int /*<<< orphan*/  e1000_set_d3_lplu_state_generic ; 
 int /*<<< orphan*/  e1000_write_phy_reg_bm2 ; 
 int /*<<< orphan*/  e1000_write_phy_reg_igp ; 
 int /*<<< orphan*/  e1000_write_phy_reg_m88 ; 

__attribute__((used)) static s32 e1000_init_phy_params_82571(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;

	DEBUGFUNC("e1000_init_phy_params_82571");

	if (hw->phy.media_type != e1000_media_type_copper) {
		phy->type = e1000_phy_none;
		return E1000_SUCCESS;
	}

	phy->addr			= 1;
	phy->autoneg_mask		= AUTONEG_ADVERTISE_SPEED_DEFAULT;
	phy->reset_delay_us		= 100;

	phy->ops.check_reset_block	= e1000_check_reset_block_generic;
	phy->ops.reset			= e1000_phy_hw_reset_generic;
	phy->ops.set_d0_lplu_state	= e1000_set_d0_lplu_state_82571;
	phy->ops.set_d3_lplu_state	= e1000_set_d3_lplu_state_generic;
	phy->ops.power_up		= e1000_power_up_phy_copper;
	phy->ops.power_down		= e1000_power_down_phy_copper_82571;

	switch (hw->mac.type) {
	case e1000_82571:
	case e1000_82572:
		phy->type		= e1000_phy_igp_2;
		phy->ops.get_cfg_done	= e1000_get_cfg_done_82571;
		phy->ops.get_info	= e1000_get_phy_info_igp;
		phy->ops.check_polarity	= e1000_check_polarity_igp;
		phy->ops.force_speed_duplex = e1000_phy_force_speed_duplex_igp;
		phy->ops.get_cable_length = e1000_get_cable_length_igp_2;
		phy->ops.read_reg	= e1000_read_phy_reg_igp;
		phy->ops.write_reg	= e1000_write_phy_reg_igp;
		phy->ops.acquire	= e1000_get_hw_semaphore;
		phy->ops.release	= e1000_put_hw_semaphore;
		break;
	case e1000_82573:
		phy->type		= e1000_phy_m88;
		phy->ops.get_cfg_done	= e1000_get_cfg_done_generic;
		phy->ops.get_info	= e1000_get_phy_info_m88;
		phy->ops.check_polarity	= e1000_check_polarity_m88;
		phy->ops.commit		= e1000_phy_sw_reset_generic;
		phy->ops.force_speed_duplex = e1000_phy_force_speed_duplex_m88;
		phy->ops.get_cable_length = e1000_get_cable_length_m88;
		phy->ops.read_reg	= e1000_read_phy_reg_m88;
		phy->ops.write_reg	= e1000_write_phy_reg_m88;
		phy->ops.acquire	= e1000_get_hw_semaphore;
		phy->ops.release	= e1000_put_hw_semaphore;
		break;
	case e1000_82574:
	case e1000_82583:

		phy->type		= e1000_phy_bm;
		phy->ops.get_cfg_done	= e1000_get_cfg_done_generic;
		phy->ops.get_info	= e1000_get_phy_info_m88;
		phy->ops.check_polarity	= e1000_check_polarity_m88;
		phy->ops.commit		= e1000_phy_sw_reset_generic;
		phy->ops.force_speed_duplex = e1000_phy_force_speed_duplex_m88;
		phy->ops.get_cable_length = e1000_get_cable_length_m88;
		phy->ops.read_reg	= e1000_read_phy_reg_bm2;
		phy->ops.write_reg	= e1000_write_phy_reg_bm2;
		phy->ops.acquire	= e1000_get_hw_semaphore_82574;
		phy->ops.release	= e1000_put_hw_semaphore_82574;
		phy->ops.set_d0_lplu_state = e1000_set_d0_lplu_state_82574;
		phy->ops.set_d3_lplu_state = e1000_set_d3_lplu_state_82574;
		break;
	default:
		return -E1000_ERR_PHY;
		break;
	}

	/* This can only be done after all function pointers are setup. */
	ret_val = e1000_get_phy_id_82571(hw);
	if (ret_val) {
		DEBUGOUT("Error getting PHY ID\n");
		return ret_val;
	}

	/* Verify phy id */
	switch (hw->mac.type) {
	case e1000_82571:
	case e1000_82572:
		if (phy->id != IGP01E1000_I_PHY_ID)
			ret_val = -E1000_ERR_PHY;
		break;
	case e1000_82573:
		if (phy->id != M88E1111_I_PHY_ID)
			ret_val = -E1000_ERR_PHY;
		break;
	case e1000_82574:
	case e1000_82583:
		if (phy->id != BME1000_E_PHY_ID_R2)
			ret_val = -E1000_ERR_PHY;
		break;
	default:
		ret_val = -E1000_ERR_PHY;
		break;
	}

	if (ret_val)
		DEBUGOUT1("PHY ID unknown: type = 0x%08x\n", phy->id);

	return ret_val;
}