#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t num_idx; int /*<<< orphan*/ * idx; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_state ;
typedef  int /*<<< orphan*/  bhnd_sprom_opcode_idx_entry ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 

bhnd_sprom_opcode_idx_entry *
bhnd_sprom_opcode_index_next(bhnd_sprom_opcode_state *state,
    bhnd_sprom_opcode_idx_entry *prev)
{
	size_t idxpos;

	/* Get next index position */
	if (prev == NULL) {
		idxpos = 0;
	} else {
		/* Determine current position */
		idxpos = (size_t)(prev - state->idx);
		BHND_NV_ASSERT(idxpos < state->num_idx,
		    ("invalid index %zu", idxpos));

		/* Advance to next entry */
		idxpos++;
	}

	/* Check for EOF */
	if (idxpos == state->num_idx)
		return (NULL);

	return (&state->idx[idxpos]);
}