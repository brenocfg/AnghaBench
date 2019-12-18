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
typedef  void* u_int ;
struct pt_regs {int pc; int pr; int sr; void** regs; } ;
struct mem_access {int dummy; } ;
typedef  int insn_size_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  PERF_COUNT_SW_ALIGNMENT_FAULTS ; 
 int SH_PC_12BIT_OFFSET (int) ; 
 int SH_PC_8BIT_OFFSET (int) ; 
 int /*<<< orphan*/  current ; 
 int handle_delayslot (struct pt_regs*,int,struct mem_access*) ; 
 int handle_unaligned_ins (int,struct pt_regs*,struct mem_access*) ; 
 int instruction_size (int) ; 
 int /*<<< orphan*/  perf_sw_event (int /*<<< orphan*/ ,int,struct pt_regs*,unsigned long) ; 
 int /*<<< orphan*/  unaligned_fixups_notify (int /*<<< orphan*/ ,int,struct pt_regs*) ; 

int handle_unaligned_access(insn_size_t instruction, struct pt_regs *regs,
			    struct mem_access *ma, int expected,
			    unsigned long address)
{
	u_int rm;
	int ret, index;

	/*
	 * XXX: We can't handle mixed 16/32-bit instructions yet
	 */
	if (instruction_size(instruction) != 2)
		return -EINVAL;

	index = (instruction>>8)&15;	/* 0x0F00 */
	rm = regs->regs[index];

	/*
	 * Log the unexpected fixups, and then pass them on to perf.
	 *
	 * We intentionally don't report the expected cases to perf as
	 * otherwise the trapped I/O case will skew the results too much
	 * to be useful.
	 */
	if (!expected) {
		unaligned_fixups_notify(current, instruction, regs);
		perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1,
			      regs, address);
	}

	ret = -EFAULT;
	switch (instruction&0xF000) {
	case 0x0000:
		if (instruction==0x000B) {
			/* rts */
			ret = handle_delayslot(regs, instruction, ma);
			if (ret==0)
				regs->pc = regs->pr;
		}
		else if ((instruction&0x00FF)==0x0023) {
			/* braf @Rm */
			ret = handle_delayslot(regs, instruction, ma);
			if (ret==0)
				regs->pc += rm + 4;
		}
		else if ((instruction&0x00FF)==0x0003) {
			/* bsrf @Rm */
			ret = handle_delayslot(regs, instruction, ma);
			if (ret==0) {
				regs->pr = regs->pc + 4;
				regs->pc += rm + 4;
			}
		}
		else {
			/* mov.[bwl] to/from memory via r0+rn */
			goto simple;
		}
		break;

	case 0x1000: /* mov.l Rm,@(disp,Rn) */
		goto simple;

	case 0x2000: /* mov.[bwl] to memory, possibly with pre-decrement */
		goto simple;

	case 0x4000:
		if ((instruction&0x00FF)==0x002B) {
			/* jmp @Rm */
			ret = handle_delayslot(regs, instruction, ma);
			if (ret==0)
				regs->pc = rm;
		}
		else if ((instruction&0x00FF)==0x000B) {
			/* jsr @Rm */
			ret = handle_delayslot(regs, instruction, ma);
			if (ret==0) {
				regs->pr = regs->pc + 4;
				regs->pc = rm;
			}
		}
		else {
			/* mov.[bwl] to/from memory via r0+rn */
			goto simple;
		}
		break;

	case 0x5000: /* mov.l @(disp,Rm),Rn */
		goto simple;

	case 0x6000: /* mov.[bwl] from memory, possibly with post-increment */
		goto simple;

	case 0x8000: /* bf lab, bf/s lab, bt lab, bt/s lab */
		switch (instruction&0x0F00) {
		case 0x0100: /* mov.w R0,@(disp,Rm) */
			goto simple;
		case 0x0500: /* mov.w @(disp,Rm),R0 */
			goto simple;
		case 0x0B00: /* bf   lab - no delayslot*/
			ret = 0;
			break;
		case 0x0F00: /* bf/s lab */
			ret = handle_delayslot(regs, instruction, ma);
			if (ret==0) {
#if defined(CONFIG_CPU_SH4) || defined(CONFIG_SH7705_CACHE_32KB)
				if ((regs->sr & 0x00000001) != 0)
					regs->pc += 4; /* next after slot */
				else
#endif
					regs->pc += SH_PC_8BIT_OFFSET(instruction);
			}
			break;
		case 0x0900: /* bt   lab - no delayslot */
			ret = 0;
			break;
		case 0x0D00: /* bt/s lab */
			ret = handle_delayslot(regs, instruction, ma);
			if (ret==0) {
#if defined(CONFIG_CPU_SH4) || defined(CONFIG_SH7705_CACHE_32KB)
				if ((regs->sr & 0x00000001) == 0)
					regs->pc += 4; /* next after slot */
				else
#endif
					regs->pc += SH_PC_8BIT_OFFSET(instruction);
			}
			break;
		}
		break;

	case 0x9000: /* mov.w @(disp,Rm),Rn */
		goto simple;

	case 0xA000: /* bra label */
		ret = handle_delayslot(regs, instruction, ma);
		if (ret==0)
			regs->pc += SH_PC_12BIT_OFFSET(instruction);
		break;

	case 0xB000: /* bsr label */
		ret = handle_delayslot(regs, instruction, ma);
		if (ret==0) {
			regs->pr = regs->pc + 4;
			regs->pc += SH_PC_12BIT_OFFSET(instruction);
		}
		break;

	case 0xD000: /* mov.l @(disp,Rm),Rn */
		goto simple;
	}
	return ret;

	/* handle non-delay-slot instruction */
 simple:
	ret = handle_unaligned_ins(instruction, regs, ma);
	if (ret==0)
		regs->pc += instruction_size(instruction);
	return ret;
}