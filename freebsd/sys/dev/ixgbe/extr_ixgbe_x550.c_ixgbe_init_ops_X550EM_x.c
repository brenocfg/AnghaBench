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
struct TYPE_4__ {int /*<<< orphan*/ * init_led_link_act; int /*<<< orphan*/ * setup_eee; int /*<<< orphan*/ * setup_fc; int /*<<< orphan*/  release_swfw_sync; int /*<<< orphan*/  acquire_swfw_sync; int /*<<< orphan*/  write_iosf_sb_reg; int /*<<< orphan*/  read_iosf_sb_reg; } ;
struct ixgbe_mac_info {TYPE_2__ ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  write_link_unlocked; int /*<<< orphan*/  write_link; int /*<<< orphan*/  read_link_unlocked; int /*<<< orphan*/  read_link; } ;
struct ixgbe_link_info {int /*<<< orphan*/  addr; TYPE_1__ ops; } ;
struct ixgbe_hw {scalar_t__ device_id; struct ixgbe_link_info link; struct ixgbe_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_CS4227 ; 
 scalar_t__ IXGBE_DEV_ID_X550EM_X_1G_T ; 
 int /*<<< orphan*/  ixgbe_acquire_swfw_sync_X550em ; 
 int /*<<< orphan*/  ixgbe_init_ops_X550EM (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_read_i2c_combined_generic ; 
 int /*<<< orphan*/  ixgbe_read_i2c_combined_generic_unlocked ; 
 int /*<<< orphan*/  ixgbe_read_iosf_sb_reg_x550 ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync_X550em ; 
 int /*<<< orphan*/  ixgbe_write_i2c_combined_generic ; 
 int /*<<< orphan*/  ixgbe_write_i2c_combined_generic_unlocked ; 
 int /*<<< orphan*/  ixgbe_write_iosf_sb_reg_x550 ; 

s32 ixgbe_init_ops_X550EM_x(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	struct ixgbe_link_info *link = &hw->link;
	s32 ret_val;

	DEBUGFUNC("ixgbe_init_ops_X550EM_x");

	/* Start with generic X550EM init */
	ret_val = ixgbe_init_ops_X550EM(hw);

	mac->ops.read_iosf_sb_reg = ixgbe_read_iosf_sb_reg_x550;
	mac->ops.write_iosf_sb_reg = ixgbe_write_iosf_sb_reg_x550;
	mac->ops.acquire_swfw_sync = ixgbe_acquire_swfw_sync_X550em;
	mac->ops.release_swfw_sync = ixgbe_release_swfw_sync_X550em;
	link->ops.read_link = ixgbe_read_i2c_combined_generic;
	link->ops.read_link_unlocked = ixgbe_read_i2c_combined_generic_unlocked;
	link->ops.write_link = ixgbe_write_i2c_combined_generic;
	link->ops.write_link_unlocked =
				      ixgbe_write_i2c_combined_generic_unlocked;
	link->addr = IXGBE_CS4227;

	if (hw->device_id == IXGBE_DEV_ID_X550EM_X_1G_T) {
		mac->ops.setup_fc = NULL;
		mac->ops.setup_eee = NULL;
		mac->ops.init_led_link_act = NULL;
	}

	return ret_val;
}