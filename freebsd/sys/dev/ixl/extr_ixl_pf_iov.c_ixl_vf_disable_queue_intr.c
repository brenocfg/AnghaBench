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
 int /*<<< orphan*/  I40E_VFINT_DYN_CTLN_CLEARPBA_MASK ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_vf_disable_queue_intr(struct i40e_hw *hw, uint32_t vfint_reg)
{

	wr32(hw, vfint_reg, I40E_VFINT_DYN_CTLN_CLEARPBA_MASK);
	ixl_flush(hw);
}