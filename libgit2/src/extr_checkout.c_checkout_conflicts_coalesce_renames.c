#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_index_name_entry ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_8__ {int /*<<< orphan*/  update_conflicts; int /*<<< orphan*/  target; } ;
typedef  TYPE_1__ checkout_data ;
struct TYPE_9__ {int name_collision; int one_to_two; int /*<<< orphan*/ * ours; int /*<<< orphan*/ * theirs; } ;
typedef  TYPE_2__ checkout_conflictdata ;

/* Variables and functions */
 int /*<<< orphan*/  checkout_conflictdata_empty ; 
 int checkout_conflicts_load_byname_entry (TYPE_2__**,TYPE_2__**,TYPE_2__**,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 size_t git_index_name_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_index_name_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * git_iterator_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_remove_matching (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int checkout_conflicts_coalesce_renames(
	checkout_data *data)
{
	git_index *index;
	const git_index_name_entry *name_entry;
	checkout_conflictdata *ancestor_conflict, *our_conflict, *their_conflict;
	size_t i, names;
	int error = 0;

	if ((index = git_iterator_index(data->target)) == NULL)
		return 0;

	/* Juggle entries based on renames */
	names = git_index_name_entrycount(index);

	for (i = 0; i < names; i++) {
		name_entry = git_index_name_get_byindex(index, i);

		if ((error = checkout_conflicts_load_byname_entry(
			&ancestor_conflict, &our_conflict, &their_conflict,
			data, name_entry)) < 0)
			goto done;

		if (our_conflict && our_conflict != ancestor_conflict) {
			ancestor_conflict->ours = our_conflict->ours;
			our_conflict->ours = NULL;

			if (our_conflict->theirs)
				our_conflict->name_collision = 1;

			if (our_conflict->name_collision)
				ancestor_conflict->name_collision = 1;
		}

		if (their_conflict && their_conflict != ancestor_conflict) {
			ancestor_conflict->theirs = their_conflict->theirs;
			their_conflict->theirs = NULL;

			if (their_conflict->ours)
				their_conflict->name_collision = 1;

			if (their_conflict->name_collision)
				ancestor_conflict->name_collision = 1;
		}

		if (our_conflict && our_conflict != ancestor_conflict &&
			their_conflict && their_conflict != ancestor_conflict)
			ancestor_conflict->one_to_two = 1;
	}

	git_vector_remove_matching(
		&data->update_conflicts, checkout_conflictdata_empty, NULL);

done:
	return error;
}