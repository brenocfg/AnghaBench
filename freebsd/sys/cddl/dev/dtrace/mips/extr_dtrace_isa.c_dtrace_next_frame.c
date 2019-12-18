#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int register_t ;
struct TYPE_7__ {int rs; int rt; scalar_t__ imm; } ;
struct TYPE_6__ {int /*<<< orphan*/  rs; int /*<<< orphan*/  func; } ;
struct TYPE_5__ {int op; } ;
struct TYPE_8__ {unsigned int word; TYPE_3__ IType; TYPE_2__ RType; TYPE_1__ JType; } ;
typedef  TYPE_4__ InstFmt ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_IS_VALID_KERNELADDR (int) ; 
#define  OP_ADDI 151 
#define  OP_ADDIU 150 
#define  OP_BCOND 149 
#define  OP_BCx 148 
#define  OP_BCy 147 
#define  OP_BEQ 146 
#define  OP_BGTZ 145 
#define  OP_BLEZ 144 
#define  OP_BNE 143 
#define  OP_BREAK 142 
#define  OP_COP0 141 
#define  OP_COP1 140 
#define  OP_COP2 139 
#define  OP_COP3 138 
#define  OP_DADDI 137 
#define  OP_DADDIU 136 
#define  OP_J 135 
#define  OP_JAL 134 
#define  OP_JALR 133 
#define  OP_JR 132 
#define  OP_SD 131 
#define  OP_SPECIAL 130 
#define  OP_SW 129 
#define  OP_SYSCALL 128 
 void* kdbpeek (int*) ; 
 int kdbpeekd (int*) ; 

__attribute__((used)) static int
dtrace_next_frame(register_t *pc, register_t *sp,
	register_t *args, int *valid_args)
{
	InstFmt i;
	/*
	 * Arrays for a0..a3 registers and flags if content
	 * of these registers is valid, e.g. obtained from the stack
	 */
	uintptr_t va;
	unsigned instr, mask;
	unsigned int frames = 0;
	int more, stksize;
	register_t ra = 0;
	int arg, r;
	vm_offset_t addr;

	/*
	 * Invalidate arguments values
	 */
	if (valid_args) {
		for (r = 0; r < 8; r++)
			valid_args[r] = 0;
	}

	/* Jump here after a nonstandard (interrupt handler) frame */
	stksize = 0;
	if (frames++ > 100) {
		/* return breaks stackframe-size heuristics with gcc -O2 */
		goto error;	/* XXX */
	}

	/* check for bad SP: could foul up next frame */
	if (!MIPS_IS_VALID_KERNELADDR(*sp)) {
		goto error;
	}

	/* check for bad PC */
	if (!MIPS_IS_VALID_KERNELADDR(*pc)) {
		goto error;
	}

	/*
	 * Find the beginning of the current subroutine by scanning
	 * backwards from the current PC for the end of the previous
	 * subroutine.
	 */
	va = *pc - sizeof(int);
	while (1) {
		instr = kdbpeek((int *)va);

		/* [d]addiu sp,sp,-X */
		if (((instr & 0xffff8000) == 0x27bd8000)
		    || ((instr & 0xffff8000) == 0x67bd8000))
			break;

		/* jr	ra */
		if (instr == 0x03e00008) {
			/* skip over branch-delay slot instruction */
			va += 2 * sizeof(int);
			break;
		}

		va -= sizeof(int);
	}

	/* skip over nulls which might separate .o files */
	while ((instr = kdbpeek((int *)va)) == 0)
		va += sizeof(int);

	/* scan forwards to find stack size and any saved registers */
	stksize = 0;
	more = 3;
	mask = 0;
	for (; more; va += sizeof(int),
	    more = (more == 3) ? 3 : more - 1) {
		/* stop if hit our current position */
		if (va >= *pc)
			break;
		instr = kdbpeek((int *)va);
		i.word = instr;
		switch (i.JType.op) {
		case OP_SPECIAL:
			switch (i.RType.func) {
			case OP_JR:
			case OP_JALR:
				more = 2;	/* stop after next instruction */
				break;

			case OP_SYSCALL:
			case OP_BREAK:
				more = 1;	/* stop now */
			};
			break;

		case OP_BCOND:
		case OP_J:
		case OP_JAL:
		case OP_BEQ:
		case OP_BNE:
		case OP_BLEZ:
		case OP_BGTZ:
			more = 2;	/* stop after next instruction */
			break;

		case OP_COP0:
		case OP_COP1:
		case OP_COP2:
		case OP_COP3:
			switch (i.RType.rs) {
			case OP_BCx:
			case OP_BCy:
				more = 2;	/* stop after next instruction */
			};
			break;

		case OP_SW:
			/* look for saved registers on the stack */
			if (i.IType.rs != 29)
				break;
			/* only restore the first one */
			if (mask & (1 << i.IType.rt))
				break;
			mask |= (1 << i.IType.rt);
			addr = (vm_offset_t)(*sp + (short)i.IType.imm);
			switch (i.IType.rt) {
			case 4:/* a0 */
			case 5:/* a1 */
			case 6:/* a2 */
			case 7:/* a3 */
#if defined(__mips_n64) || defined(__mips_n32)
			case 8:/* a4 */
			case 9:/* a5 */
			case 10:/* a6 */
			case 11:/* a7 */
#endif
				arg = i.IType.rt - 4;
				if (args)
					args[arg] = kdbpeek((int*)addr);
				if (valid_args)
					valid_args[arg] = 1;
				break;
			case 31:	/* ra */
				ra = kdbpeek((int *)addr);
			}
			break;

		case OP_SD:
			/* look for saved registers on the stack */
			if (i.IType.rs != 29)
				break;
			/* only restore the first one */
			if (mask & (1 << i.IType.rt))
				break;
			mask |= (1 << i.IType.rt);
			addr = (vm_offset_t)(*sp + (short)i.IType.imm);
			switch (i.IType.rt) {
			case 4:/* a0 */
			case 5:/* a1 */
			case 6:/* a2 */
			case 7:/* a3 */
#if defined(__mips_n64) || defined(__mips_n32)
			case 8:/* a4 */
			case 9:/* a5 */
			case 10:/* a6 */
			case 11:/* a7 */
#endif
				arg = i.IType.rt - 4;
				if (args)
					args[arg] = kdbpeekd((int *)addr);
				if (valid_args)
					valid_args[arg] = 1;
				break;

			case 31:	/* ra */
				ra = kdbpeekd((int *)addr);
			}
			break;

		case OP_ADDI:
		case OP_ADDIU:
		case OP_DADDI:
		case OP_DADDIU:
			/* look for stack pointer adjustment */
			if (i.IType.rs != 29 || i.IType.rt != 29)
				break;
			stksize = -((short)i.IType.imm);
		}
	}

	if (!MIPS_IS_VALID_KERNELADDR(ra)) 
		return (-1);

	*pc = ra;
	*sp += stksize;

#if defined(__mips_o32)
	/*
	 * For MIPS32 fill out arguments 5..8 from the stack
	 */
	for (arg = 4; arg < 8; arg++) {
		addr = (vm_offset_t)(*sp + arg*sizeof(register_t));
		if (args)
			args[arg] = kdbpeekd((int *)addr);
		if (valid_args)
			valid_args[arg] = 1;
	}
#endif

	return (0);
error:
	return (-1);
}