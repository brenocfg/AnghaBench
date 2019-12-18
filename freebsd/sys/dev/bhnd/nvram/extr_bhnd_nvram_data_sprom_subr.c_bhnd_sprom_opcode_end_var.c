#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ var_state; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_state ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SPROM_OPCODE_VAR_STATE_DONE ; 
 scalar_t__ SPROM_OPCODE_VAR_STATE_OPEN ; 
 int /*<<< orphan*/  SPROM_OP_BAD (TYPE_1__*,char*) ; 

__attribute__((used)) static int
bhnd_sprom_opcode_end_var(bhnd_sprom_opcode_state *state)
{
	if (state->var_state != SPROM_OPCODE_VAR_STATE_OPEN) {
		SPROM_OP_BAD(state, "no open variable definition\n");
		return (EINVAL);
	}

	state->var_state = SPROM_OPCODE_VAR_STATE_DONE;
	return (0);
}