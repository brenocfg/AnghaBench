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
struct thread_info {unsigned long ksp; scalar_t__ new_child; } ;
struct task_struct {int dummy; } ;
struct reg_window {unsigned long* locals; unsigned long* ins; } ;

/* Variables and functions */
 int GDB_F0 ; 
 int GDB_F62 ; 
 size_t GDB_FPRS ; 
 size_t GDB_FSR ; 
 int GDB_G0 ; 
 int GDB_G6 ; 
 size_t GDB_G7 ; 
 int GDB_I0 ; 
 int GDB_L0 ; 
 size_t GDB_NPC ; 
 int GDB_O0 ; 
 size_t GDB_O7 ; 
 size_t GDB_PC ; 
 int GDB_SP ; 
 size_t GDB_STATE ; 
 size_t GDB_Y ; 
 scalar_t__ STACK_BIAS ; 
 size_t TI_FLAG_BYTE_CWP ; 
 unsigned long TSTATE_IE ; 
 unsigned long TSTATE_PRIV ; 
 unsigned long* __thread_flag_byte_ptr (struct thread_info*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *p)
{
	struct thread_info *t = task_thread_info(p);
	extern unsigned int switch_to_pc;
	extern unsigned int ret_from_fork;
	struct reg_window *win;
	unsigned long pc, cwp;
	int i;

	for (i = GDB_G0; i < GDB_G6; i++)
		gdb_regs[i] = 0;
	gdb_regs[GDB_G6] = (unsigned long) t;
	gdb_regs[GDB_G7] = (unsigned long) p;
	for (i = GDB_O0; i < GDB_SP; i++)
		gdb_regs[i] = 0;
	gdb_regs[GDB_SP] = t->ksp;
	gdb_regs[GDB_O7] = 0;

	win = (struct reg_window *) (t->ksp + STACK_BIAS);
	for (i = 0; i < 8; i++)
		gdb_regs[GDB_L0 + i] = win->locals[i];
	for (i = 0; i < 8; i++)
		gdb_regs[GDB_I0 + i] = win->ins[i];

	for (i = GDB_F0; i <= GDB_F62; i++)
		gdb_regs[i] = 0;

	if (t->new_child)
		pc = (unsigned long) &ret_from_fork;
	else
		pc = (unsigned long) &switch_to_pc;

	gdb_regs[GDB_PC] = pc;
	gdb_regs[GDB_NPC] = pc + 4;

	cwp = __thread_flag_byte_ptr(t)[TI_FLAG_BYTE_CWP];

	gdb_regs[GDB_STATE] = (TSTATE_PRIV | TSTATE_IE | cwp);
	gdb_regs[GDB_FSR] = 0;
	gdb_regs[GDB_FPRS] = 0;
	gdb_regs[GDB_Y] = 0;
}