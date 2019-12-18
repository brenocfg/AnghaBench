#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long sp; unsigned long pc; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {unsigned long* regs; unsigned long pr; unsigned long gbr; } ;

/* Variables and functions */
 int DBG_MAX_REG_NUM ; 
 size_t GDB_GBR ; 
 size_t GDB_PC ; 
 size_t GDB_PR ; 
 int GDB_R15 ; 
 int GDB_R8 ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *p)
{
	struct pt_regs *thread_regs = task_pt_regs(p);
	int reg;

	/* Initialize to zero */
	for (reg = 0; reg < DBG_MAX_REG_NUM; reg++)
		gdb_regs[reg] = 0;

	/*
	 * Copy out GP regs 8 to 14.
	 *
	 * switch_to() relies on SR.RB toggling, so regs 0->7 are banked
	 * and need privileged instructions to get to. The r15 value we
	 * fetch from the thread info directly.
	 */
	for (reg = GDB_R8; reg < GDB_R15; reg++)
		gdb_regs[reg] = thread_regs->regs[reg];

	gdb_regs[GDB_R15] = p->thread.sp;
	gdb_regs[GDB_PC] = p->thread.pc;

	/*
	 * Additional registers we have context for
	 */
	gdb_regs[GDB_PR] = thread_regs->pr;
	gdb_regs[GDB_GBR] = thread_regs->gbr;
}