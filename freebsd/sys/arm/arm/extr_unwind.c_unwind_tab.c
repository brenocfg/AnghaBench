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
typedef  int uint32_t ;
struct unwind_state {scalar_t__* registers; int* insn; int byte; int entries; scalar_t__ start_pc; int update_mask; } ;

/* Variables and functions */
 int ENTRY_ARM_LU16 ; 
 int ENTRY_ARM_SU16 ; 
 int ENTRY_MASK ; 
 size_t LR ; 
 size_t PC ; 
 int /*<<< orphan*/  db_printf (char*,int) ; 
 scalar_t__ unwind_exec_insn (struct unwind_state*) ; 

__attribute__((used)) static int
unwind_tab(struct unwind_state *state)
{
	uint32_t entry;

	/* Set PC to a known value */
	state->registers[PC] = 0;

	/* Read the personality */
	entry = *state->insn & ENTRY_MASK;

	if (entry == ENTRY_ARM_SU16) {
		state->byte = 2;
		state->entries = 1;
	} else if (entry == ENTRY_ARM_LU16) {
		state->byte = 1;
		state->entries = ((*state->insn >> 16) & 0xFF) + 1;
	} else {
#if 0
		db_printf("Unknown entry: %x\n", entry);
#endif
		return 1;
	}

	while (state->entries > 0) {
		if (unwind_exec_insn(state) != 0)
			return 1;
	}

	/*
	 * The program counter was not updated, load it from the link register.
	 */
	if (state->registers[PC] == 0) {
		state->registers[PC] = state->registers[LR];

		/*
		 * If the program counter changed, flag it in the update mask.
		 */
		if (state->start_pc != state->registers[PC])
			state->update_mask |= 1 << PC;
	}

	return 0;
}