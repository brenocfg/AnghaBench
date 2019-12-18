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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  rsts; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;
struct TYPE_6__ {int type; } ;
struct ixgbe_hw {TYPE_2__ mbx; TYPE_3__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  IXGBE_ERR_MBX ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_VFLRE (int) ; 
 int /*<<< orphan*/  IXGBE_VFLREC (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 

__attribute__((used)) static s32 ixgbe_check_for_rst_pf(struct ixgbe_hw *hw, u16 vf_number)
{
	u32 reg_offset = (vf_number < 32) ? 0 : 1;
	u32 vf_shift = vf_number % 32;
	u32 vflre = 0;
	s32 ret_val = IXGBE_ERR_MBX;

	DEBUGFUNC("ixgbe_check_for_rst_pf");

	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
		vflre = IXGBE_READ_REG(hw, IXGBE_VFLRE(reg_offset));
		break;
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_X550EM_a:
	case ixgbe_mac_X540:
		vflre = IXGBE_READ_REG(hw, IXGBE_VFLREC(reg_offset));
		break;
	default:
		break;
	}

	if (vflre & (1 << vf_shift)) {
		ret_val = IXGBE_SUCCESS;
		IXGBE_WRITE_REG(hw, IXGBE_VFLREC(reg_offset), (1 << vf_shift));
		hw->mbx.stats.rsts++;
	}

	return ret_val;
}