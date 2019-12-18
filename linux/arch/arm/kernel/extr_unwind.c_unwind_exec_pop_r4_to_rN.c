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
struct unwind_ctrl_block {unsigned long* vrs; } ;

/* Variables and functions */
 size_t SP ; 
 int URC_FAILURE ; 
 int URC_OK ; 
 scalar_t__ unwind_pop_register (struct unwind_ctrl_block*,unsigned long**,int) ; 

__attribute__((used)) static int unwind_exec_pop_r4_to_rN(struct unwind_ctrl_block *ctrl,
					unsigned long insn)
{
	unsigned long *vsp = (unsigned long *)ctrl->vrs[SP];
	int reg;

	/* pop R4-R[4+bbb] */
	for (reg = 4; reg <= 4 + (insn & 7); reg++)
		if (unwind_pop_register(ctrl, &vsp, reg))
				return -URC_FAILURE;

	if (insn & 0x8)
		if (unwind_pop_register(ctrl, &vsp, 14))
				return -URC_FAILURE;

	ctrl->vrs[SP] = (unsigned long)vsp;

	return URC_OK;
}