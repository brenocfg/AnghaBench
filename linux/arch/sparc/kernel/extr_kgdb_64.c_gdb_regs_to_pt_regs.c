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
struct reg_window {unsigned long* locals; unsigned long* ins; } ;
struct pt_regs {unsigned long* u_regs; unsigned long tstate; unsigned long tpc; unsigned long tnpc; unsigned long y; } ;

/* Variables and functions */
 int GDB_G1 ; 
 int GDB_I0 ; 
 int GDB_L0 ; 
 size_t GDB_NPC ; 
 size_t GDB_PC ; 
 size_t GDB_STATE ; 
 size_t GDB_Y ; 
 scalar_t__ STACK_BIAS ; 
 unsigned long TSTATE_CWP ; 
 size_t UREG_FP ; 
 int UREG_G1 ; 

void gdb_regs_to_pt_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
	struct reg_window *win;
	int i;

	for (i = 0; i < 15; i++)
		regs->u_regs[UREG_G1 + i] = gdb_regs[GDB_G1 + i];

	/* If the TSTATE register is changing, we have to preserve
	 * the CWP field, otherwise window save/restore explodes.
	 */
	if (regs->tstate != gdb_regs[GDB_STATE]) {
		unsigned long cwp = regs->tstate & TSTATE_CWP;

		regs->tstate = (gdb_regs[GDB_STATE] & ~TSTATE_CWP) | cwp;
	}

	regs->tpc = gdb_regs[GDB_PC];
	regs->tnpc = gdb_regs[GDB_NPC];
	regs->y = gdb_regs[GDB_Y];

	win = (struct reg_window *) (regs->u_regs[UREG_FP] + STACK_BIAS);
	for (i = 0; i < 8; i++)
		win->locals[i] = gdb_regs[GDB_L0 + i];
	for (i = 0; i < 8; i++)
		win->ins[i] = gdb_regs[GDB_I0 + i];
}