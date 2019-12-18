#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int have_bind; } ;
struct TYPE_6__ {scalar_t__ var_state; TYPE_1__ var; } ;
typedef  TYPE_2__ bhnd_sprom_opcode_state ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int EINVAL ; 
 int ENOENT ; 
#define  SPROM_OPCODE_DO_BIND 131 
#define  SPROM_OPCODE_DO_BINDN 130 
#define  SPROM_OPCODE_DO_BINDN_IMM 129 
 int SPROM_OPCODE_OP (int /*<<< orphan*/ ) ; 
#define  SPROM_OPCODE_VAR_END 128 
 scalar_t__ SPROM_OPCODE_VAR_STATE_DONE ; 
 scalar_t__ SPROM_OPCODE_VAR_STATE_OPEN ; 
 int bhnd_sprom_opcode_step (TYPE_2__*,int /*<<< orphan*/ *) ; 

int
bhnd_sprom_opcode_next_binding(bhnd_sprom_opcode_state *state)
{
	uint8_t	opcode;
	int	error;

	if (state->var_state != SPROM_OPCODE_VAR_STATE_OPEN)
		return (EINVAL);

	/* Step until we hit a bind opcode, or a new variable */
	while ((error = bhnd_sprom_opcode_step(state, &opcode)) == 0) {
		switch (SPROM_OPCODE_OP(opcode)) {
		case SPROM_OPCODE_DO_BIND:
		case SPROM_OPCODE_DO_BINDN:
		case SPROM_OPCODE_DO_BINDN_IMM:
			/* Found next bind */
			BHND_NV_ASSERT(
			    state->var_state == SPROM_OPCODE_VAR_STATE_OPEN,
			    ("missing variable definition"));
			BHND_NV_ASSERT(state->var.have_bind, ("missing bind"));

			return (0);

		case SPROM_OPCODE_VAR_END:
			/* No further binding opcodes */ 
			BHND_NV_ASSERT(
			    state->var_state == SPROM_OPCODE_VAR_STATE_DONE,
			    ("variable definition still available"));
			return (ENOENT);
		}
	}

	/* Not found, or evaluation failed */
	return (error);
}