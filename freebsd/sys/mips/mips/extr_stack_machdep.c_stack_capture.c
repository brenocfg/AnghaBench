#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_register_t ;
struct stack {int dummy; } ;
typedef  int /*<<< orphan*/  insn ;
struct TYPE_6__ {int /*<<< orphan*/  rs; int /*<<< orphan*/  func; } ;
struct TYPE_5__ {int op; scalar_t__ imm; int /*<<< orphan*/  rt; int /*<<< orphan*/  rs; } ;
struct TYPE_7__ {int word; TYPE_2__ RType; TYPE_1__ IType; } ;
typedef  TYPE_3__ InstFmt ;

/* Variables and functions */
#define  OP_ADDI 134 
#define  OP_ADDIU 133 
#define  OP_DADDI 132 
#define  OP_DADDIU 131 
 int /*<<< orphan*/  OP_JR ; 
#define  OP_SD 130 
#define  OP_SPECIAL 129 
#define  OP_SW 128 
 int /*<<< orphan*/  RA ; 
 int /*<<< orphan*/  SP ; 
 int /*<<< orphan*/  bcopy (void*,TYPE_3__*,int) ; 
 scalar_t__ btext ; 
 int stack_put (struct stack*,scalar_t__) ; 
 scalar_t__ stack_register_fetch (scalar_t__,short) ; 
 int /*<<< orphan*/  stack_zero (struct stack*) ; 

__attribute__((used)) static void
stack_capture(struct stack *st, u_register_t pc, u_register_t sp)
{
	u_register_t  ra = 0, i, stacksize;
	short ra_stack_pos = 0;
	InstFmt insn;

	stack_zero(st);

	for (;;) {
		stacksize = 0;
		if (pc <= (u_register_t)(intptr_t)btext)
			break;
		for (i = pc; i >= (u_register_t)(intptr_t)btext; i -= sizeof (insn)) {
			bcopy((void *)(intptr_t)i, &insn, sizeof insn);
			switch (insn.IType.op) {
			case OP_ADDI:
			case OP_ADDIU:
			case OP_DADDI:
			case OP_DADDIU:
				if (insn.IType.rs != SP || insn.IType.rt != SP)
					break;
				stacksize = -(short)insn.IType.imm;
				break;

			case OP_SW:
			case OP_SD:
				if (insn.IType.rs != SP || insn.IType.rt != RA)
					break;
				ra_stack_pos = (short)insn.IType.imm;
				break;
			default:
				break;
			}

			if (stacksize)
				break;
		}

		if (stack_put(st, pc) == -1)
			break;

		for (i = pc; !ra; i += sizeof (insn)) {
			bcopy((void *)(intptr_t)i, &insn, sizeof insn);

			switch (insn.IType.op) {
			case OP_SPECIAL:
				if (insn.RType.func == OP_JR) {
					if (ra >= (u_register_t)(intptr_t)btext)
						break;
					if (insn.RType.rs != RA)
						break;
					ra = stack_register_fetch(sp, 
					    ra_stack_pos);
					if (!ra)
						goto done;
					ra -= 8;
				}
				break;
			default:
				break;
			}
			/* eret */
			if (insn.word == 0x42000018)
				goto done;
		}

		if (pc == ra && stacksize == 0)
			break;

		sp += stacksize;
		pc = ra;
		ra = 0;
	}
done:
	return;
}