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
struct TYPE_2__ {unsigned long r4; unsigned long r5; unsigned long r6; unsigned long r7; unsigned long r8; unsigned long r9; unsigned long sl; unsigned long fp; unsigned long sp; unsigned long pc; } ;
struct thread_info {TYPE_1__ cpu_context; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int GDB_MAX_REGS ; 
 size_t _FP ; 
 size_t _PC ; 
 size_t _R10 ; 
 size_t _R4 ; 
 size_t _R5 ; 
 size_t _R6 ; 
 size_t _R7 ; 
 size_t _R8 ; 
 size_t _R9 ; 
 size_t _SPT ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

void
sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *task)
{
	struct thread_info *ti;
	int regno;

	/* Just making sure... */
	if (task == NULL)
		return;

	/* Initialize to zero */
	for (regno = 0; regno < GDB_MAX_REGS; regno++)
		gdb_regs[regno] = 0;

	/* Otherwise, we have only some registers from switch_to() */
	ti			= task_thread_info(task);
	gdb_regs[_R4]		= ti->cpu_context.r4;
	gdb_regs[_R5]		= ti->cpu_context.r5;
	gdb_regs[_R6]		= ti->cpu_context.r6;
	gdb_regs[_R7]		= ti->cpu_context.r7;
	gdb_regs[_R8]		= ti->cpu_context.r8;
	gdb_regs[_R9]		= ti->cpu_context.r9;
	gdb_regs[_R10]		= ti->cpu_context.sl;
	gdb_regs[_FP]		= ti->cpu_context.fp;
	gdb_regs[_SPT]		= ti->cpu_context.sp;
	gdb_regs[_PC]		= ti->cpu_context.pc;
}