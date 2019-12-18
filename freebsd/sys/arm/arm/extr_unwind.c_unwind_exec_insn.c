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
struct unwind_state {unsigned int* registers; scalar_t__ entries; int update_mask; } ;

/* Variables and functions */
 size_t FP ; 
 unsigned int INSN_FINISH ; 
 unsigned int INSN_POP_COUNT ; 
 unsigned int INSN_POP_COUNT_MASK ; 
 unsigned int INSN_POP_MASKED ; 
 unsigned int INSN_POP_REGS ; 
 unsigned int INSN_POP_TYPE_MASK ; 
 unsigned int INSN_STD_DATA_MASK ; 
 unsigned int INSN_STD_MASK ; 
 unsigned int INSN_VSP_DEC ; 
 unsigned int INSN_VSP_INC ; 
 unsigned int INSN_VSP_LARGE_INC ; 
 unsigned int INSN_VSP_LARGE_INC_MASK ; 
 unsigned int INSN_VSP_MASK ; 
 unsigned int INSN_VSP_REG ; 
 unsigned int INSN_VSP_SIZE_MASK ; 
 size_t LR ; 
 size_t PC ; 
 size_t SP ; 
 int /*<<< orphan*/  db_printf (char*,int,...) ; 
 unsigned int unwind_exec_read_byte (struct unwind_state*) ; 

__attribute__((used)) static int
unwind_exec_insn(struct unwind_state *state)
{
	unsigned int insn;
	uint32_t *vsp = (uint32_t *)state->registers[SP];
	int update_vsp = 0;

	/* This should never happen */
	if (state->entries == 0)
		return 1;

	/* Read the next instruction */
	insn = unwind_exec_read_byte(state);

	if ((insn & INSN_VSP_MASK) == INSN_VSP_INC) {
		state->registers[SP] += ((insn & INSN_VSP_SIZE_MASK) << 2) + 4;

	} else if ((insn & INSN_VSP_MASK) == INSN_VSP_DEC) {
		state->registers[SP] -= ((insn & INSN_VSP_SIZE_MASK) << 2) + 4;

	} else if ((insn & INSN_STD_MASK) == INSN_POP_MASKED) {
		unsigned int mask, reg;

		/* Load the mask */
		mask = unwind_exec_read_byte(state);
		mask |= (insn & INSN_STD_DATA_MASK) << 8;

		/* We have a refuse to unwind instruction */
		if (mask == 0)
			return 1;

		/* Update SP */
		update_vsp = 1;

		/* Load the registers */
		for (reg = 4; mask && reg < 16; mask >>= 1, reg++) {
			if (mask & 1) {
				state->registers[reg] = *vsp++;
				state->update_mask |= 1 << reg;

				/* If we have updated SP kep its value */
				if (reg == SP)
					update_vsp = 0;
			}
		}

	} else if ((insn & INSN_STD_MASK) == INSN_VSP_REG &&
	    ((insn & INSN_STD_DATA_MASK) != 13) &&
	    ((insn & INSN_STD_DATA_MASK) != 15)) {
		/* sp = register */
		state->registers[SP] =
		    state->registers[insn & INSN_STD_DATA_MASK];

	} else if ((insn & INSN_STD_MASK) == INSN_POP_COUNT) {
		unsigned int count, reg;

		/* Read how many registers to load */
		count = insn & INSN_POP_COUNT_MASK;

		/* Update sp */
		update_vsp = 1;

		/* Pop the registers */
		for (reg = 4; reg <= 4 + count; reg++) {
			state->registers[reg] = *vsp++;
			state->update_mask |= 1 << reg;
		}

		/* Check if we are in the pop r14 version */
		if ((insn & INSN_POP_TYPE_MASK) != 0) {
			state->registers[14] = *vsp++;
		}

	} else if (insn == INSN_FINISH) {
		/* Stop processing */
		state->entries = 0;

	} else if (insn == INSN_POP_REGS) {
		unsigned int mask, reg;

		mask = unwind_exec_read_byte(state);
		if (mask == 0 || (mask & 0xf0) != 0)
			return 1;

		/* Update SP */
		update_vsp = 1;

		/* Load the registers */
		for (reg = 0; mask && reg < 4; mask >>= 1, reg++) {
			if (mask & 1) {
				state->registers[reg] = *vsp++;
				state->update_mask |= 1 << reg;
			}
		}

	} else if ((insn & INSN_VSP_LARGE_INC_MASK) == INSN_VSP_LARGE_INC) {
		unsigned int uleb128;

		/* Read the increment value */
		uleb128 = unwind_exec_read_byte(state);

		state->registers[SP] += 0x204 + (uleb128 << 2);

	} else {
		/* We hit a new instruction that needs to be implemented */
#if 0
		db_printf("Unhandled instruction %.2x\n", insn);
#endif
		return 1;
	}

	if (update_vsp) {
		state->registers[SP] = (uint32_t)vsp;
	}

#if 0
	db_printf("fp = %08x, sp = %08x, lr = %08x, pc = %08x\n",
	    state->registers[FP], state->registers[SP], state->registers[LR],
	    state->registers[PC]);
#endif

	return 0;
}