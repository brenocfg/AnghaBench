#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t offset; size_t vid; size_t input; TYPE_1__* layout; } ;
typedef  TYPE_2__ bhnd_sprom_opcode_state ;
struct TYPE_9__ {size_t offset; size_t vid; size_t opcodes; } ;
typedef  TYPE_3__ bhnd_sprom_opcode_idx_entry ;
struct TYPE_7__ {size_t bindings; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SPROM_OP_BAD (TYPE_2__*,char*,size_t) ; 
 size_t UINT16_MAX ; 

int
bhnd_sprom_opcode_init_entry(bhnd_sprom_opcode_state *state,
    bhnd_sprom_opcode_idx_entry *entry)
{
	size_t opcodes;

	/* We limit the SPROM index representations to the minimal type widths
	 * capable of covering all known layouts */

	/* Save SPROM image offset */
	if (state->offset > UINT16_MAX) {
		SPROM_OP_BAD(state, "cannot index large offset %u\n",
		    state->offset);
		return (ENXIO);
	}

	entry->offset = state->offset;

	/* Save current variable ID */
	if (state->vid > UINT16_MAX) {
		SPROM_OP_BAD(state, "cannot index large vid %zu\n",
		    state->vid);
		return (ENXIO);
	}
	entry->vid = state->vid;

	/* Save opcode position */
	opcodes = (state->input - state->layout->bindings);
	if (opcodes > UINT16_MAX) {
		SPROM_OP_BAD(state, "cannot index large opcode offset "
		    "%zu\n", opcodes);
		return (ENXIO);
	}
	entry->opcodes = opcodes;

	return (0);
}