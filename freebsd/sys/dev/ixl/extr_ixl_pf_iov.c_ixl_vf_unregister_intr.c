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
typedef  int /*<<< orphan*/  uint32_t ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK ; 
 int I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_MASK ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ixl_vf_unregister_intr(struct i40e_hw *hw, uint32_t vpint_reg)
{

	wr32(hw, vpint_reg, I40E_VPINT_LNKLSTN_FIRSTQ_TYPE_MASK |
	    I40E_VPINT_LNKLSTN_FIRSTQ_INDX_MASK);
	ixl_flush(hw);
}