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
struct pt_regs {unsigned long* uregs; unsigned long fp; unsigned long sp; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long *idx_to_addr(struct pt_regs *regs, int idx)
{
	/* this should be consistent with ptrace.h */
	if (idx >= 0 && idx <= 25)	/* R0-R25 */
		return &regs->uregs[0] + idx;
	else if (idx >= 28 && idx <= 30)	/* FP, GP, LP */
		return &regs->fp + (idx - 28);
	else if (idx == 31)	/* SP */
		return &regs->sp;
	else
		return NULL;	/* cause a segfault */
}