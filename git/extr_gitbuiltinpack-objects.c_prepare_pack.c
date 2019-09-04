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
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct object_entry {TYPE_1__ idx; int /*<<< orphan*/  preferred_base; scalar_t__ no_try_delta; int /*<<< orphan*/  type_valid; } ;
struct TYPE_6__ {scalar_t__ nr_objects; struct object_entry* objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct object_entry**,scalar_t__) ; 
 scalar_t__ DELTA (struct object_entry*) ; 
 int /*<<< orphan*/  QSORT (struct object_entry**,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int do_check_packed_object_crc ; 
 int /*<<< orphan*/  free (struct object_entry**) ; 
 int /*<<< orphan*/  get_object_details () ; 
 int /*<<< orphan*/  ll_find_deltas (struct object_entry**,unsigned int,int,int,unsigned int*) ; 
 scalar_t__ oe_size_less_than (TYPE_2__*,struct object_entry*,int) ; 
 scalar_t__ oe_type (struct object_entry*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_to_stdout ; 
 scalar_t__ progress ; 
 int /*<<< orphan*/  progress_state ; 
 int /*<<< orphan*/  resolve_tree_islands (int /*<<< orphan*/ ,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  start_progress (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 TYPE_2__ to_pack ; 
 int /*<<< orphan*/  type_size_sort ; 
 scalar_t__ use_delta_islands ; 

__attribute__((used)) static void prepare_pack(int window, int depth)
{
	struct object_entry **delta_list;
	uint32_t i, nr_deltas;
	unsigned n;

	if (use_delta_islands)
		resolve_tree_islands(the_repository, progress, &to_pack);

	get_object_details();

	/*
	 * If we're locally repacking then we need to be doubly careful
	 * from now on in order to make sure no stealth corruption gets
	 * propagated to the new pack.  Clients receiving streamed packs
	 * should validate everything they get anyway so no need to incur
	 * the additional cost here in that case.
	 */
	if (!pack_to_stdout)
		do_check_packed_object_crc = 1;

	if (!to_pack.nr_objects || !window || !depth)
		return;

	ALLOC_ARRAY(delta_list, to_pack.nr_objects);
	nr_deltas = n = 0;

	for (i = 0; i < to_pack.nr_objects; i++) {
		struct object_entry *entry = to_pack.objects + i;

		if (DELTA(entry))
			/* This happens if we decided to reuse existing
			 * delta from a pack.  "reuse_delta &&" is implied.
			 */
			continue;

		if (!entry->type_valid ||
		    oe_size_less_than(&to_pack, entry, 50))
			continue;

		if (entry->no_try_delta)
			continue;

		if (!entry->preferred_base) {
			nr_deltas++;
			if (oe_type(entry) < 0)
				die(_("unable to get type of object %s"),
				    oid_to_hex(&entry->idx.oid));
		} else {
			if (oe_type(entry) < 0) {
				/*
				 * This object is not found, but we
				 * don't have to include it anyway.
				 */
				continue;
			}
		}

		delta_list[n++] = entry;
	}

	if (nr_deltas && n > 1) {
		unsigned nr_done = 0;
		if (progress)
			progress_state = start_progress(_("Compressing objects"),
							nr_deltas);
		QSORT(delta_list, n, type_size_sort);
		ll_find_deltas(delta_list, n, window+1, depth, &nr_done);
		stop_progress(&progress_state);
		if (nr_done != nr_deltas)
			die(_("inconsistency with delta count"));
	}
	free(delta_list);
}