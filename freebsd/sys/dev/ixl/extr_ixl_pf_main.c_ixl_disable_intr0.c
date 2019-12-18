#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_DYN_CTL0 ; 
 int I40E_PFINT_DYN_CTL0_ITR_INDX_SHIFT ; 
 int IXL_ITR_NONE ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

void
ixl_disable_intr0(struct i40e_hw *hw)
{
	u32		reg;

	reg = IXL_ITR_NONE << I40E_PFINT_DYN_CTL0_ITR_INDX_SHIFT;
	wr32(hw, I40E_PFINT_DYN_CTL0, reg);
	ixl_flush(hw);
}