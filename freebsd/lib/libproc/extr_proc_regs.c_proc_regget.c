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
typedef  int /*<<< orphan*/  regs ;
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
#define  REG_PC 129 
#define  REG_SP 128 
 size_t SP ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct reg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
proc_regget(struct proc_handle *phdl, proc_reg_t reg, unsigned long *regvalue)
{
	struct reg regs;

	if (phdl->status == PS_DEAD || phdl->status == PS_UNDEAD ||
	    phdl->status == PS_IDLE) {
		errno = ENOENT;
		return (-1);
	}
	memset(&regs, 0, sizeof(regs));
	if (ptrace(PT_GETREGS, proc_getpid(phdl), (caddr_t)&regs, 0) < 0)
		return (-1);
	switch (reg) {
	case REG_PC:
#if defined(__aarch64__)
		*regvalue = regs.elr;
#elif defined(__amd64__)
		*regvalue = regs.r_rip;
#elif defined(__arm__)
		*regvalue = regs.r_pc;
#elif defined(__i386__)
		*regvalue = regs.r_eip;
#elif defined(__mips__)
		*regvalue = regs.r_regs[PC];
#elif defined(__powerpc__)
		*regvalue = regs.pc;
#elif defined(__riscv)
		*regvalue = regs.sepc;
#endif
		break;
	case REG_SP:
#if defined(__aarch64__)
		*regvalue = regs.sp;
#elif defined(__amd64__)
		*regvalue = regs.r_rsp;
#elif defined(__arm__)
		*regvalue = regs.r_sp;
#elif defined(__i386__)
		*regvalue = regs.r_esp;
#elif defined(__mips__)
		*regvalue = regs.r_regs[SP];
#elif defined(__powerpc__)
		*regvalue = regs.fixreg[1];
#elif defined(__riscv)
		*regvalue = regs.sp;
#endif
		break;
	default:
		DPRINTFX("ERROR: no support for reg number %d", reg);
		return (-1);
	}

	return (0);
}