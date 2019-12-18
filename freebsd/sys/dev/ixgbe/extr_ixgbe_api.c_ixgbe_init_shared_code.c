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
struct TYPE_2__ {int type; int /*<<< orphan*/  max_link_up_time; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_ERR_DEVICE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  IXGBE_LINK_UP_TIME ; 
 int /*<<< orphan*/  ixgbe_init_ops_82598 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_ops_82599 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_ops_X540 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_ops_X550 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_ops_X550EM_a (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_init_ops_X550EM_x (struct ixgbe_hw*) ; 
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 
 int /*<<< orphan*/  ixgbe_set_mac_type (struct ixgbe_hw*) ; 

s32 ixgbe_init_shared_code(struct ixgbe_hw *hw)
{
	s32 status;

	DEBUGFUNC("ixgbe_init_shared_code");

	/*
	 * Set the mac type
	 */
	ixgbe_set_mac_type(hw);

	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		status = ixgbe_init_ops_82598(hw);
		break;
	case ixgbe_mac_82599EB:
		status = ixgbe_init_ops_82599(hw);
		break;
	case ixgbe_mac_X540:
		status = ixgbe_init_ops_X540(hw);
		break;
	case ixgbe_mac_X550:
		status = ixgbe_init_ops_X550(hw);
		break;
	case ixgbe_mac_X550EM_x:
		status = ixgbe_init_ops_X550EM_x(hw);
		break;
	case ixgbe_mac_X550EM_a:
		status = ixgbe_init_ops_X550EM_a(hw);
		break;
	default:
		status = IXGBE_ERR_DEVICE_NOT_SUPPORTED;
		break;
	}
	hw->mac.max_link_up_time = IXGBE_LINK_UP_TIME;

	return status;
}