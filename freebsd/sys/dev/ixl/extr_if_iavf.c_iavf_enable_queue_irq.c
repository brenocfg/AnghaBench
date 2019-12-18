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
 int /*<<< orphan*/  I40E_VFINT_DYN_CTLN1 (int) ; 
 int I40E_VFINT_DYN_CTLN1_CLEARPBA_MASK ; 
 int I40E_VFINT_DYN_CTLN1_INTENA_MASK ; 
 int I40E_VFINT_DYN_CTLN1_ITR_INDX_MASK ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iavf_enable_queue_irq(struct i40e_hw *hw, int id)
{
	u32		reg;

	reg = I40E_VFINT_DYN_CTLN1_INTENA_MASK |
	    I40E_VFINT_DYN_CTLN1_CLEARPBA_MASK |
	    I40E_VFINT_DYN_CTLN1_ITR_INDX_MASK;
	wr32(hw, I40E_VFINT_DYN_CTLN1(id), reg);
}