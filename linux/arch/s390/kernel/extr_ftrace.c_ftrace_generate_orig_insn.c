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
struct ftrace_insn {int opc; int disp; } ;

/* Variables and functions */

__attribute__((used)) static inline void ftrace_generate_orig_insn(struct ftrace_insn *insn)
{
#if defined(CC_USING_HOTPATCH) || defined(CC_USING_NOP_MCOUNT)
	/* brcl 0,0 */
	insn->opc = 0xc004;
	insn->disp = 0;
#else
	/* stg r14,8(r15) */
	insn->opc = 0xe3e0;
	insn->disp = 0xf0080024;
#endif
}