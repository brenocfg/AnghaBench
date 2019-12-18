#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_vardefn {int /*<<< orphan*/  nelem; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {scalar_t__ var_state; size_t vid; int /*<<< orphan*/  var; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_state ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int EINVAL ; 
 scalar_t__ SPROM_OPCODE_VAR_STATE_NONE ; 
 scalar_t__ SPROM_OPCODE_VAR_STATE_OPEN ; 
 int /*<<< orphan*/  SPROM_OP_BAD (TYPE_1__*,char*,size_t) ; 
 struct bhnd_nvram_vardefn* bhnd_nvram_get_vardefn (size_t) ; 
 int bhnd_sprom_opcode_set_nelem (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int bhnd_sprom_opcode_set_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
bhnd_sprom_opcode_set_var(bhnd_sprom_opcode_state *state, size_t vid)
{
	const struct bhnd_nvram_vardefn	*var;
	int				 error;

	BHND_NV_ASSERT(state->var_state == SPROM_OPCODE_VAR_STATE_NONE,
	    ("overwrite of open variable definition"));

	/* Locate the variable definition */
	if ((var = bhnd_nvram_get_vardefn(vid)) == NULL) {
		SPROM_OP_BAD(state, "unknown variable ID: %zu\n", vid);
		return (EINVAL);
	}

	/* Update vid and var state */
	state->vid = vid;
	state->var_state = SPROM_OPCODE_VAR_STATE_OPEN;

	/* Initialize default variable record values */
	memset(&state->var, 0x0, sizeof(state->var));

	/* Set initial base type */
	if ((error = bhnd_sprom_opcode_set_type(state, var->type)))
		return (error);

	/* Set default array length */
	if ((error = bhnd_sprom_opcode_set_nelem(state, var->nelem)))
		return (error);

	return (0);
}