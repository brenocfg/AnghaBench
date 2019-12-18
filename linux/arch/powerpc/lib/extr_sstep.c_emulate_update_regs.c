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
struct pt_regs {int nip; unsigned long* gpr; int xer; unsigned long link; int ctr; int /*<<< orphan*/  ccr; int /*<<< orphan*/  msr; } ;
struct instruction_op {int type; size_t reg; unsigned long val; int xerval; int /*<<< orphan*/  spr; int /*<<< orphan*/  ccval; } ;

/* Variables and functions */
#define  BARRIER 140 
#define  BARRIER_EIEIO 139 
#define  BARRIER_ISYNC 138 
#define  BARRIER_LWSYNC 137 
 int BARRIER_MASK ; 
#define  BARRIER_PTESYNC 136 
#define  BARRIER_SYNC 135 
#define  BRANCH 134 
 int BRTAKEN ; 
#define  COMPUTE 133 
 int DECCTR ; 
 int GETTYPE (int) ; 
#define  MFSPR 132 
#define  MTSPR 131 
 int SETCC ; 
 int SETLK ; 
 int SETREG ; 
 int SETXER ; 
#define  SPRN_CTR 130 
#define  SPRN_LR 129 
#define  SPRN_XER 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  eieio () ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  mb () ; 
 unsigned long truncate_if_32bit (int /*<<< orphan*/ ,int) ; 

void emulate_update_regs(struct pt_regs *regs, struct instruction_op *op)
{
	unsigned long next_pc;

	next_pc = truncate_if_32bit(regs->msr, regs->nip + 4);
	switch (GETTYPE(op->type)) {
	case COMPUTE:
		if (op->type & SETREG)
			regs->gpr[op->reg] = op->val;
		if (op->type & SETCC)
			regs->ccr = op->ccval;
		if (op->type & SETXER)
			regs->xer = op->xerval;
		break;

	case BRANCH:
		if (op->type & SETLK)
			regs->link = next_pc;
		if (op->type & BRTAKEN)
			next_pc = op->val;
		if (op->type & DECCTR)
			--regs->ctr;
		break;

	case BARRIER:
		switch (op->type & BARRIER_MASK) {
		case BARRIER_SYNC:
			mb();
			break;
		case BARRIER_ISYNC:
			isync();
			break;
		case BARRIER_EIEIO:
			eieio();
			break;
		case BARRIER_LWSYNC:
			asm volatile("lwsync" : : : "memory");
			break;
		case BARRIER_PTESYNC:
			asm volatile("ptesync" : : : "memory");
			break;
		}
		break;

	case MFSPR:
		switch (op->spr) {
		case SPRN_XER:
			regs->gpr[op->reg] = regs->xer & 0xffffffffUL;
			break;
		case SPRN_LR:
			regs->gpr[op->reg] = regs->link;
			break;
		case SPRN_CTR:
			regs->gpr[op->reg] = regs->ctr;
			break;
		default:
			WARN_ON_ONCE(1);
		}
		break;

	case MTSPR:
		switch (op->spr) {
		case SPRN_XER:
			regs->xer = op->val & 0xffffffffUL;
			break;
		case SPRN_LR:
			regs->link = op->val;
			break;
		case SPRN_CTR:
			regs->ctr = op->val;
			break;
		default:
			WARN_ON_ONCE(1);
		}
		break;

	default:
		WARN_ON_ONCE(1);
	}
	regs->nip = next_pc;
}