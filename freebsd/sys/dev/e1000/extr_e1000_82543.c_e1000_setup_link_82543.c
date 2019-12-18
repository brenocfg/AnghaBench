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
struct TYPE_5__ {int (* read ) (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ nvm; TYPE_1__ mac; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_ERR_NVM ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NVM_INIT_CONTROL2_REG ; 
 int NVM_SWDPIO_EXT_SHIFT ; 
 int NVM_WORD0F_SWPDIO_EXT_MASK ; 
 scalar_t__ e1000_82543 ; 
 int e1000_setup_link_generic (struct e1000_hw*) ; 
 int stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static s32 e1000_setup_link_82543(struct e1000_hw *hw)
{
	u32 ctrl_ext;
	s32  ret_val;
	u16 data;

	DEBUGFUNC("e1000_setup_link_82543");

	/*
	 * Take the 4 bits from NVM word 0xF that determine the initial
	 * polarity value for the SW controlled pins, and setup the
	 * Extended Device Control reg with that info.
	 * This is needed because one of the SW controlled pins is used for
	 * signal detection.  So this should be done before phy setup.
	 */
	if (hw->mac.type == e1000_82543) {
		ret_val = hw->nvm.ops.read(hw, NVM_INIT_CONTROL2_REG, 1, &data);
		if (ret_val) {
			DEBUGOUT("NVM Read Error\n");
			ret_val = -E1000_ERR_NVM;
			goto out;
		}
		ctrl_ext = ((data & NVM_WORD0F_SWPDIO_EXT_MASK) <<
			    NVM_SWDPIO_EXT_SHIFT);
		E1000_WRITE_REG(hw, E1000_CTRL_EXT, ctrl_ext);
	}

	ret_val = e1000_setup_link_generic(hw);

out:
	return ret_val;
}