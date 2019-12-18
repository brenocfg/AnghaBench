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
struct pt_regs {int pc; int sr; int* regs; long pr; } ;
typedef  int /*<<< orphan*/  insn_size_t ;

/* Variables and functions */
 scalar_t__ OPCODE_BF (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_BFS (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_BRA (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_BRAF (int /*<<< orphan*/ ) ; 
 size_t OPCODE_BRAF_REG (int /*<<< orphan*/ ) ; 
 int OPCODE_BRA_DISP (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_BSR (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_BSRF (int /*<<< orphan*/ ) ; 
 size_t OPCODE_BSRF_REG (int /*<<< orphan*/ ) ; 
 int OPCODE_BSR_DISP (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_BT (int /*<<< orphan*/ ) ; 
 int OPCODE_BTF_DISP (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_BTS (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_JMP (int /*<<< orphan*/ ) ; 
 size_t OPCODE_JMP_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_JSR (int /*<<< orphan*/ ) ; 
 size_t OPCODE_JSR_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_RTE (int /*<<< orphan*/ ) ; 
 scalar_t__ OPCODE_RTS (int /*<<< orphan*/ ) ; 
 int SR_T_BIT_MASK ; 
 int /*<<< orphan*/  __raw_readw (int) ; 
 int /*<<< orphan*/  flush_icache_range (long,long) ; 
 long instruction_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static short *get_step_address(struct pt_regs *linux_regs)
{
	insn_size_t op = __raw_readw(linux_regs->pc);
	long addr;

	/* BT */
	if (OPCODE_BT(op)) {
		if (linux_regs->sr & SR_T_BIT_MASK)
			addr = linux_regs->pc + 4 + OPCODE_BTF_DISP(op);
		else
			addr = linux_regs->pc + 2;
	}

	/* BTS */
	else if (OPCODE_BTS(op)) {
		if (linux_regs->sr & SR_T_BIT_MASK)
			addr = linux_regs->pc + 4 + OPCODE_BTF_DISP(op);
		else
			addr = linux_regs->pc + 4;	/* Not in delay slot */
	}

	/* BF */
	else if (OPCODE_BF(op)) {
		if (!(linux_regs->sr & SR_T_BIT_MASK))
			addr = linux_regs->pc + 4 + OPCODE_BTF_DISP(op);
		else
			addr = linux_regs->pc + 2;
	}

	/* BFS */
	else if (OPCODE_BFS(op)) {
		if (!(linux_regs->sr & SR_T_BIT_MASK))
			addr = linux_regs->pc + 4 + OPCODE_BTF_DISP(op);
		else
			addr = linux_regs->pc + 4;	/* Not in delay slot */
	}

	/* BRA */
	else if (OPCODE_BRA(op))
		addr = linux_regs->pc + 4 + OPCODE_BRA_DISP(op);

	/* BRAF */
	else if (OPCODE_BRAF(op))
		addr = linux_regs->pc + 4
		    + linux_regs->regs[OPCODE_BRAF_REG(op)];

	/* BSR */
	else if (OPCODE_BSR(op))
		addr = linux_regs->pc + 4 + OPCODE_BSR_DISP(op);

	/* BSRF */
	else if (OPCODE_BSRF(op))
		addr = linux_regs->pc + 4
		    + linux_regs->regs[OPCODE_BSRF_REG(op)];

	/* JMP */
	else if (OPCODE_JMP(op))
		addr = linux_regs->regs[OPCODE_JMP_REG(op)];

	/* JSR */
	else if (OPCODE_JSR(op))
		addr = linux_regs->regs[OPCODE_JSR_REG(op)];

	/* RTS */
	else if (OPCODE_RTS(op))
		addr = linux_regs->pr;

	/* RTE */
	else if (OPCODE_RTE(op))
		addr = linux_regs->regs[15];

	/* Other */
	else
		addr = linux_regs->pc + instruction_size(op);

	flush_icache_range(addr, addr + instruction_size(op));
	return (short *)addr;
}