#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct bhnd_sprom_layout {size_t num_vars; } ;
typedef  int /*<<< orphan*/  idx ;
struct TYPE_7__ {size_t num_idx; int /*<<< orphan*/ * idx; struct bhnd_sprom_layout const* layout; } ;
typedef  TYPE_1__ bhnd_sprom_opcode_state ;
typedef  int /*<<< orphan*/  bhnd_sprom_opcode_idx_entry ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_LOG (char*,int) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  SPROM_OP_BAD (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/ * bhnd_nv_calloc (size_t,int) ; 
 int /*<<< orphan*/  bhnd_nv_free (int /*<<< orphan*/ *) ; 
 int bhnd_sprom_opcode_init_entry (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int bhnd_sprom_opcode_next_var (TYPE_1__*) ; 
 int bhnd_sprom_opcode_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  bhnd_sprom_opcode_sort_idx ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 

int
bhnd_sprom_opcode_init(bhnd_sprom_opcode_state *state,
    const struct bhnd_sprom_layout *layout)
{
	bhnd_sprom_opcode_idx_entry	*idx;
	size_t				 num_vars, num_idx;
	int				 error;

	idx = NULL;

	state->layout = layout;
	state->idx = NULL;
	state->num_idx = 0;

	/* Initialize interpretation state */
	if ((error = bhnd_sprom_opcode_reset(state)))
		return (error);

	/* Allocate and populate our opcode index */
	num_idx = state->layout->num_vars;
	idx = bhnd_nv_calloc(num_idx, sizeof(*idx));
	if (idx == NULL)
		return (ENOMEM);

	for (num_vars = 0; num_vars < num_idx; num_vars++) {
		/* Seek to next entry */
		if ((error = bhnd_sprom_opcode_next_var(state))) {
			SPROM_OP_BAD(state, "error reading expected variable "
			    "entry: %d\n", error);
			bhnd_nv_free(idx);
			return (error);
		}

		/* Record entry state in our index */
		error = bhnd_sprom_opcode_init_entry(state, &idx[num_vars]);
		if (error) {
			SPROM_OP_BAD(state, "error initializing index for "
			    "entry: %d\n", error);
			bhnd_nv_free(idx);
			return (error);
		}
	}

	/* Should have reached end of binding table; next read must return
	 * ENOENT */
	if ((error = bhnd_sprom_opcode_next_var(state)) != ENOENT) {
		BHND_NV_LOG("expected EOF parsing binding table: %d\n", error);
		bhnd_nv_free(idx);
		return (ENXIO);
	}

	/* Reset interpretation state */
	if ((error = bhnd_sprom_opcode_reset(state))) {
		bhnd_nv_free(idx);
		return (error);
	}

	/* Make index available to opcode state evaluation */
        qsort(idx, num_idx, sizeof(idx[0]), bhnd_sprom_opcode_sort_idx);

	state->idx = idx;
	state->num_idx = num_idx;

	return (0);
}