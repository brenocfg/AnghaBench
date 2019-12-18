#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ var_state; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_state ;
typedef  int /*<<< orphan*/  bhnd_sprom_opcode_idx_entry ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 scalar_t__ SPROM_OPCODE_OP (int /*<<< orphan*/ ) ; 
 scalar_t__ SPROM_OPCODE_VAR_END ; 
 scalar_t__ SPROM_OPCODE_VAR_STATE_DONE ; 
 int bhnd_sprom_opcode_seek (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int bhnd_sprom_opcode_step (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
bhnd_sprom_opcode_eval_var(bhnd_sprom_opcode_state *state,
    bhnd_sprom_opcode_idx_entry *entry)
{
	uint8_t	opcode;
	int	error;

	/* Seek to entry */
	if ((error = bhnd_sprom_opcode_seek(state, entry)))
		return (error);

	/* Parse full variable definition */
	while ((error = bhnd_sprom_opcode_step(state, &opcode)) == 0) {
		/* Iterate until VAR_END */
		if (SPROM_OPCODE_OP(opcode) != SPROM_OPCODE_VAR_END)
			continue;

		BHND_NV_ASSERT(state->var_state == SPROM_OPCODE_VAR_STATE_DONE,
		    ("incomplete variable definition"));

		return (0);
	}

	/* Error parsing definition */
	return (error);
}