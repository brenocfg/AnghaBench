#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  bind_total; } ;
struct TYPE_8__ {int var_state; TYPE_1__ var; } ;
typedef  TYPE_2__ bhnd_sprom_opcode_state ;

/* Variables and functions */
 int SPROM_OPCODE_DO_BIND ; 
 int SPROM_OPCODE_OP (int) ; 
 int SPROM_OPCODE_VAR_END ; 
#define  SPROM_OPCODE_VAR_STATE_DONE 130 
#define  SPROM_OPCODE_VAR_STATE_NONE 129 
#define  SPROM_OPCODE_VAR_STATE_OPEN 128 
 int SPROM_OP_BIND_SKIP_IN_SHIFT ; 
 int SPROM_OP_BIND_SKIP_IN_SIGN ; 
 int SPROM_OP_BIND_SKIP_OUT_SHIFT ; 
 int /*<<< orphan*/  SPROM_OP_IS_IMPLICIT_VAR_END (int) ; 
 int /*<<< orphan*/  SPROM_OP_IS_VAR_END (int) ; 
 int bhnd_sprom_opcode_clear_var (TYPE_2__*) ; 
 int bhnd_sprom_opcode_end_var (TYPE_2__*) ; 
 int bhnd_sprom_opcode_set_bind (TYPE_2__*,int,int,int,int) ; 

__attribute__((used)) static int
bhnd_sprom_opcode_rewrite_opcode(bhnd_sprom_opcode_state *state,
    uint8_t *opcode)
{
	uint8_t	op;
	int	error;

	op = SPROM_OPCODE_OP(*opcode);
	switch (state->var_state) {
	case SPROM_OPCODE_VAR_STATE_NONE:
		/* No open variable definition */
		return (0);

	case SPROM_OPCODE_VAR_STATE_OPEN:
		/* Open variable definition; check for implicit closure. */

		/*
		 * If a variable definition contains no explicit bind
		 * instructions prior to closure, we must generate a DO_BIND
		 * instruction with count and skip values of 1.
		 */
		if (SPROM_OP_IS_VAR_END(op) &&
		    state->var.bind_total == 0)
		{
			uint8_t	count, skip_in, skip_out;
			bool	skip_in_negative;

			/* Create bind with skip_in/skip_out of 1, count of 1 */
			count = 1;
			skip_in = 1;
			skip_out = 1;
			skip_in_negative = false;

			error = bhnd_sprom_opcode_set_bind(state, count,
			    skip_in, skip_in_negative, skip_out);
			if (error)
				return (error);

			/* Return DO_BIND */
			*opcode = SPROM_OPCODE_DO_BIND |
			    (0 << SPROM_OP_BIND_SKIP_IN_SIGN) |
			    (1 << SPROM_OP_BIND_SKIP_IN_SHIFT) |
			    (1 << SPROM_OP_BIND_SKIP_OUT_SHIFT);

			return (0);
		}

		/*
		 * If a variable is implicitly closed (e.g. by a new variable
		 * definition), we must generate a VAR_END instruction.
		 */
		if (SPROM_OP_IS_IMPLICIT_VAR_END(op)) {
			/* Mark as complete */
			if ((error = bhnd_sprom_opcode_end_var(state)))
				return (error);

			/* Return VAR_END */
			*opcode = SPROM_OPCODE_VAR_END;
			return (0);
		}
		break;


	case SPROM_OPCODE_VAR_STATE_DONE:
		/* Previously completed variable definition. Discard variable
		 * state */
		return (bhnd_sprom_opcode_clear_var(state));
	}

	/* Nothing to do */
	return (0);
}