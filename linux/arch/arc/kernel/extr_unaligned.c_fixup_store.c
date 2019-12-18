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
struct pt_regs {int dummy; } ;
struct disasm_state {int aa; int src3; int zz; int fault; scalar_t__ src2; int /*<<< orphan*/  src1; int /*<<< orphan*/  wb_reg; } ;
struct callee_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put16_unaligned_check (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put32_unaligned_check (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_reg (int /*<<< orphan*/ ,scalar_t__,struct pt_regs*,struct callee_regs*) ; 

__attribute__((used)) static void fixup_store(struct disasm_state *state, struct pt_regs *regs,
			struct callee_regs *cregs)
{
	/* register write back */
	if ((state->aa == 1) || (state->aa == 2)) {
		set_reg(state->wb_reg, state->src2 + state->src3, regs, cregs);

		if (state->aa == 3)
			state->src3 = 0;
	} else if (state->aa == 3) {
		if (state->zz == 2) {
			set_reg(state->wb_reg, state->src2 + (state->src3 << 1),
				regs, cregs);
		} else if (!state->zz) {
			set_reg(state->wb_reg, state->src2 + (state->src3 << 2),
				regs, cregs);
		} else {
			goto fault;
		}
	}

	/* write fix-up */
	if (!state->zz)
		put32_unaligned_check(state->src1, state->src2 + state->src3);
	else
		put16_unaligned_check(state->src1, state->src2 + state->src3);

	return;

fault:	state->fault = 1;
}