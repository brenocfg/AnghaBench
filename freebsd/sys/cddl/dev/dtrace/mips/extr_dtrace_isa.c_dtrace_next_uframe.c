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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int register_t ;
struct TYPE_8__ {int /*<<< orphan*/  cpuc_dtrace_flags; } ;
struct TYPE_6__ {int rs; int rt; scalar_t__ imm; } ;
struct TYPE_5__ {int op; } ;
struct TYPE_7__ {TYPE_2__ IType; TYPE_1__ JType; void* word; } ;
typedef  TYPE_3__ InstFmt ;

/* Variables and functions */
 int volatile CPU_DTRACE_FAULT ; 
 int MAX_FUNCTION_SIZE ; 
 int MAX_PROLOGUE_SIZE ; 
#define  OP_ADDI 133 
#define  OP_ADDIU 132 
#define  OP_DADDI 131 
#define  OP_DADDIU 130 
#define  OP_SD 129 
#define  OP_SW 128 
 TYPE_4__* cpu_core ; 
 size_t curcpu ; 
 void* dtrace_fuword32 (void*) ; 
 int dtrace_fuword64 (void*) ; 

__attribute__((used)) static int
dtrace_next_uframe(register_t *pc, register_t *sp, register_t *ra)
{
	int offset, registers_on_stack;
	uint32_t opcode, mask;
	register_t function_start;
	int stksize;
	InstFmt i;

	volatile uint16_t *flags =
	    (volatile uint16_t *)&cpu_core[curcpu].cpuc_dtrace_flags;

	registers_on_stack = 0;
	mask = 0;
	function_start = 0;
	offset = 0;
	stksize = 0;

	while (offset < MAX_FUNCTION_SIZE) {
		opcode = dtrace_fuword32((void *)(vm_offset_t)(*pc - offset));

		if (*flags & CPU_DTRACE_FAULT)
			goto fault;

		/* [d]addiu sp, sp, -X*/
		if (((opcode & 0xffff8000) == 0x27bd8000)
		    || ((opcode & 0xffff8000) == 0x67bd8000)) {
			function_start = *pc - offset;
			registers_on_stack = 1;
			break;
		}

		/* lui gp, X */
		if ((opcode & 0xffff8000) == 0x3c1c0000) {
			/*
			 * Function might start with this instruction
			 * Keep an eye on "jr ra" and sp correction
			 * with positive value further on
			 */
			function_start = *pc - offset;
		}

		if (function_start) {
			/* 
			 * Stop looking further. Possible end of
			 * function instruction: it means there is no
			 * stack modifications, sp is unchanged
			 */

			/* [d]addiu sp,sp,X */
			if (((opcode & 0xffff8000) == 0x27bd0000)
			    || ((opcode & 0xffff8000) == 0x67bd0000))
				break;

			if (opcode == 0x03e00008)
				break;
		}

		offset += sizeof(int);
	}

	if (!function_start)
		return (-1);

	if (registers_on_stack) {
		offset = 0;
		while ((offset < MAX_PROLOGUE_SIZE) 
		    && ((function_start + offset) < *pc)) {
			i.word = 
			    dtrace_fuword32((void *)(vm_offset_t)(function_start + offset));
			switch (i.JType.op) {
			case OP_SW:
				/* look for saved registers on the stack */
				if (i.IType.rs != 29)
					break;
				/* only restore the first one */
				if (mask & (1 << i.IType.rt))
					break;
				mask |= (1 << i.IType.rt);
				if (i.IType.rt == 31)
					*ra = dtrace_fuword32((void *)(vm_offset_t)(*sp + (short)i.IType.imm));
				break;

			case OP_SD:
				/* look for saved registers on the stack */
				if (i.IType.rs != 29)
					break;
				/* only restore the first one */
				if (mask & (1 << i.IType.rt))
					break;
				mask |= (1 << i.IType.rt);
				/* ra */
				if (i.IType.rt == 31)
					*ra = dtrace_fuword64((void *)(vm_offset_t)(*sp + (short)i.IType.imm));
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

			offset += sizeof(int);

			if (*flags & CPU_DTRACE_FAULT)
				goto fault;
		}
	}

	/*
	 * We reached the end of backtrace
	 */
	if (*pc == *ra)
		return (-1);

	*pc = *ra;
	*sp += stksize;

	return (0);
fault:
	/*
	 * We just got lost in backtrace, no big deal
	 */
	*flags &= ~CPU_DTRACE_FAULT;
	return (-1);
}