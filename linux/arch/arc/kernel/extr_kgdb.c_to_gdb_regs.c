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
struct pt_regs {unsigned long fp; unsigned long sp; unsigned long blink; unsigned long ret; unsigned long status32; unsigned long lp_count; unsigned long lp_end; unsigned long lp_start; unsigned long bta; } ;
struct callee_regs {int dummy; } ;

/* Variables and functions */
 int GDB_MAX_REGS ; 
 size_t _BLINK ; 
 size_t _BTA ; 
 size_t _FP ; 
 size_t _LP_COUNT ; 
 size_t _LP_END ; 
 size_t _LP_START ; 
 int _R0 ; 
 size_t _RET ; 
 size_t _STATUS32 ; 
 size_t _STOP_PC ; 
 size_t __SP ; 
 unsigned long get_reg (int,struct pt_regs*,struct callee_regs*) ; 

__attribute__((used)) static void to_gdb_regs(unsigned long *gdb_regs, struct pt_regs *kernel_regs,
			struct callee_regs *cregs)
{
	int regno;

	for (regno = 0; regno <= 26; regno++)
		gdb_regs[_R0 + regno] = get_reg(regno, kernel_regs, cregs);

	for (regno = 27; regno < GDB_MAX_REGS; regno++)
		gdb_regs[regno] = 0;

	gdb_regs[_FP]		= kernel_regs->fp;
	gdb_regs[__SP]		= kernel_regs->sp;
	gdb_regs[_BLINK]	= kernel_regs->blink;
	gdb_regs[_RET]		= kernel_regs->ret;
	gdb_regs[_STATUS32]	= kernel_regs->status32;
	gdb_regs[_LP_COUNT]	= kernel_regs->lp_count;
	gdb_regs[_LP_END]	= kernel_regs->lp_end;
	gdb_regs[_LP_START]	= kernel_regs->lp_start;
	gdb_regs[_BTA]		= kernel_regs->bta;
	gdb_regs[_STOP_PC]	= kernel_regs->ret;
}