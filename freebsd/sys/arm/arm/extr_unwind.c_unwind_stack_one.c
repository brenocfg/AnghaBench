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
typedef  unsigned int uint32_t ;
struct unwind_state {unsigned int* insn; int /*<<< orphan*/  start_pc; int /*<<< orphan*/ * registers; scalar_t__ update_mask; } ;
struct unwind_idx {unsigned int insn; } ;

/* Variables and functions */
 unsigned int EXIDX_CANTUNWIND ; 
 size_t PC ; 
 scalar_t__ expand_prel31 (unsigned int) ; 
 struct unwind_idx* find_index (int /*<<< orphan*/ ,int) ; 
 int unwind_tab (struct unwind_state*) ; 

int
unwind_stack_one(struct unwind_state *state, int can_lock)
{
	struct unwind_idx *index;
	int finished;

	/* Reset the mask of updated registers */
	state->update_mask = 0;

	/* The pc value is correct and will be overwritten, save it */
	state->start_pc = state->registers[PC];

	/* Find the item to run */
	index = find_index(state->start_pc, can_lock);

	finished = 0;
	if (index->insn != EXIDX_CANTUNWIND) {
		if (index->insn & (1U << 31)) {
			/* The data is within the instruction */
			state->insn = &index->insn;
		} else {
			/* A prel31 offset to the unwind table */
			state->insn = (uint32_t *)
			    ((uintptr_t)&index->insn +
			     expand_prel31(index->insn));
		}
		/* Run the unwind function */
		finished = unwind_tab(state);
	}

	/* This is the top of the stack, finish */
	if (index->insn == EXIDX_CANTUNWIND)
		finished = 1;

	return (finished);
}