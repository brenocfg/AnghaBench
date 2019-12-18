#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {int (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_7__ {TYPE_1__ ops; } ;
struct TYPE_10__ {int (* read ) (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ;} ;
struct TYPE_9__ {TYPE_5__ ops; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_2__ phy; TYPE_4__ nvm; TYPE_3__ mac; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int E1000_ERR_PHY ; 
 int E1000_SUCCESS ; 
 int /*<<< orphan*/  M88E1000_PHY_GEN_CONTROL ; 
 int /*<<< orphan*/  M88E1000_PHY_PAGE_SELECT ; 
 int NVM_PHY_CLASS_A ; 
 int /*<<< orphan*/  NVM_PHY_CLASS_WORD ; 
 int NVM_RESERVED_WORD ; 
 scalar_t__ e1000_82545_rev_3 ; 
 int stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_set_phy_mode_82540(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;
	u16 nvm_data;

	DEBUGFUNC("e1000_set_phy_mode_82540");

	if (hw->mac.type != e1000_82545_rev_3)
		goto out;

	ret_val = hw->nvm.ops.read(hw, NVM_PHY_CLASS_WORD, 1, &nvm_data);
	if (ret_val) {
		ret_val = -E1000_ERR_PHY;
		goto out;
	}

	if ((nvm_data != NVM_RESERVED_WORD) && (nvm_data & NVM_PHY_CLASS_A)) {
		ret_val = hw->phy.ops.write_reg(hw, M88E1000_PHY_PAGE_SELECT,
						0x000B);
		if (ret_val) {
			ret_val = -E1000_ERR_PHY;
			goto out;
		}
		ret_val = hw->phy.ops.write_reg(hw, M88E1000_PHY_GEN_CONTROL,
						0x8104);
		if (ret_val) {
			ret_val = -E1000_ERR_PHY;
			goto out;
		}

	}

out:
	return ret_val;
}