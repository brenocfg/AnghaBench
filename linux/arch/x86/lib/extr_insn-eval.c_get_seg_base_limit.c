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
struct pt_regs {int dummy; } ;
struct insn {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long get_seg_limit (struct pt_regs*,int) ; 
 unsigned long insn_get_seg_base (struct pt_regs*,int) ; 
 int resolve_seg_reg (struct insn*,struct pt_regs*,int) ; 

__attribute__((used)) static int get_seg_base_limit(struct insn *insn, struct pt_regs *regs,
			      int regoff, unsigned long *base,
			      unsigned long *limit)
{
	int seg_reg_idx;

	if (!base)
		return -EINVAL;

	seg_reg_idx = resolve_seg_reg(insn, regs, regoff);
	if (seg_reg_idx < 0)
		return seg_reg_idx;

	*base = insn_get_seg_base(regs, seg_reg_idx);
	if (*base == -1L)
		return -EINVAL;

	if (!limit)
		return 0;

	*limit = get_seg_limit(regs, seg_reg_idx);
	if (!(*limit))
		return -EINVAL;

	return 0;
}