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
struct reg {unsigned long elr; unsigned long r_rip; unsigned long r_pc; unsigned long r_eip; unsigned long* r_regs; unsigned long pc; unsigned long sepc; unsigned long sp; unsigned long r_rsp; unsigned long r_sp; unsigned long r_esp; unsigned long* fixreg; } ;
struct proc_handle {scalar_t__ status; } ;
typedef  int proc_reg_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFX (char*,int) ; 
 int /*<<< orphan*/  ENOENT ; 
 size_t PC ; 
 scalar_t__ PS_DEAD ; 
 scalar_t__ PS_IDLE ; 
 scalar_t__ PS_UNDEAD ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 int /*<<< orphan*/  PT_SETREGS ; 
#define  REG_PC 129 
#define  REG_SP 128 
 size_t SP ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
proc_regset(struct proc_handle *phdl, proc_reg_t reg, unsigned long regvalue)
{
	struct reg regs;

	if (phdl->status == PS_DEAD || phdl->status == PS_UNDEAD ||
	    phdl->status == PS_IDLE) {
		errno = ENOENT;
		return (-1);
	}
	if (ptrace(PT_GETREGS, proc_getpid(phdl), (caddr_t)&regs, 0) < 0)
		return (-1);
	switch (reg) {
	case REG_PC:
#if defined(__aarch64__)
		regs.elr = regvalue;
#elif defined(__amd64__)
		regs.r_rip = regvalue;
#elif defined(__arm__)
		regs.r_pc = regvalue;
#elif defined(__i386__)
		regs.r_eip = regvalue;
#elif defined(__mips__)
		regs.r_regs[PC] = regvalue;
#elif defined(__powerpc__)
		regs.pc = regvalue;
#elif defined(__riscv)
		regs.sepc = regvalue;
#endif
		break;
	case REG_SP:
#if defined(__aarch64__)
		regs.sp = regvalue;
#elif defined(__amd64__)
		regs.r_rsp = regvalue;
#elif defined(__arm__)
		regs.r_sp = regvalue;
#elif defined(__i386__)
		regs.r_esp = regvalue;
#elif defined(__mips__)
		regs.r_regs[SP] = regvalue;
#elif defined(__powerpc__)
		regs.fixreg[1] = regvalue;
#elif defined(__riscv)
		regs.sp = regvalue;
#endif
		break;
	default:
		DPRINTFX("ERROR: no support for reg number %d", reg);
		return (-1);
	}
	if (ptrace(PT_SETREGS, proc_getpid(phdl), (caddr_t)&regs, 0) < 0)
		return (-1);

	return (0);
}