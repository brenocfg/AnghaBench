#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* layout; int /*<<< orphan*/  revs; int /*<<< orphan*/  var_state; scalar_t__ vid; scalar_t__ offset; int /*<<< orphan*/  input; int /*<<< orphan*/  var; } ;
typedef  TYPE_2__ bhnd_sprom_opcode_state ;
struct TYPE_4__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  bindings; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPROM_OPCODE_VAR_STATE_NONE ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bhnd_sprom_opcode_reset(bhnd_sprom_opcode_state *state)
{
	memset(&state->var, 0, sizeof(state->var));

	state->input = state->layout->bindings;
	state->offset = 0;
	state->vid = 0;
	state->var_state = SPROM_OPCODE_VAR_STATE_NONE;
	bit_set(state->revs, state->layout->rev);

	return (0);
}