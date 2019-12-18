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
typedef  size_t uint32_t ;
struct object_entry {int no_try_delta; scalar_t__ type_valid; } ;
struct TYPE_3__ {size_t nr_objects; struct object_entry* objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSORT (struct object_entry**,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  big_file_threshold ; 
 int /*<<< orphan*/  break_delta_chains (struct object_entry*) ; 
 int /*<<< orphan*/  check_object (struct object_entry*) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  free (struct object_entry**) ; 
 scalar_t__ oe_size_greater_than (TYPE_1__*,struct object_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_offset_sort ; 
 scalar_t__ progress ; 
 int /*<<< orphan*/  progress_state ; 
 int /*<<< orphan*/  start_progress (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 
 TYPE_1__ to_pack ; 
 struct object_entry** xcalloc (size_t,int) ; 

__attribute__((used)) static void get_object_details(void)
{
	uint32_t i;
	struct object_entry **sorted_by_offset;

	if (progress)
		progress_state = start_progress(_("Counting objects"),
						to_pack.nr_objects);

	sorted_by_offset = xcalloc(to_pack.nr_objects, sizeof(struct object_entry *));
	for (i = 0; i < to_pack.nr_objects; i++)
		sorted_by_offset[i] = to_pack.objects + i;
	QSORT(sorted_by_offset, to_pack.nr_objects, pack_offset_sort);

	for (i = 0; i < to_pack.nr_objects; i++) {
		struct object_entry *entry = sorted_by_offset[i];
		check_object(entry);
		if (entry->type_valid &&
		    oe_size_greater_than(&to_pack, entry, big_file_threshold))
			entry->no_try_delta = 1;
		display_progress(progress_state, i + 1);
	}
	stop_progress(&progress_state);

	/*
	 * This must happen in a second pass, since we rely on the delta
	 * information for the whole list being completed.
	 */
	for (i = 0; i < to_pack.nr_objects; i++)
		break_delta_chains(&to_pack.objects[i]);

	free(sorted_by_offset);
}