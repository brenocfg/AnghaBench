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
struct insn {int dummy; } ;

/* Variables and functions */
 scalar_t__ __indirect_thunk_end ; 
 scalar_t__ __indirect_thunk_start ; 
 int __insn_is_indirect_jump (struct insn*) ; 
 int insn_jump_into_range (struct insn*,unsigned long,unsigned long) ; 

__attribute__((used)) static int insn_is_indirect_jump(struct insn *insn)
{
	int ret = __insn_is_indirect_jump(insn);

#ifdef CONFIG_RETPOLINE
	/*
	 * Jump to x86_indirect_thunk_* is treated as an indirect jump.
	 * Note that even with CONFIG_RETPOLINE=y, the kernel compiled with
	 * older gcc may use indirect jump. So we add this check instead of
	 * replace indirect-jump check.
	 */
	if (!ret)
		ret = insn_jump_into_range(insn,
				(unsigned long)__indirect_thunk_start,
				(unsigned long)__indirect_thunk_end -
				(unsigned long)__indirect_thunk_start);
#endif
	return ret;
}