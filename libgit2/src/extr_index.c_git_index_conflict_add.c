#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_1__*,unsigned short) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,unsigned short) ; 
 int git_index_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int index_entry_dup (TYPE_1__**,int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  index_entry_free (TYPE_1__*) ; 
 int index_insert (int /*<<< orphan*/ *,TYPE_1__**,int,int,int,int) ; 
 int /*<<< orphan*/  valid_filemode (int /*<<< orphan*/ ) ; 

int git_index_conflict_add(git_index *index,
	const git_index_entry *ancestor_entry,
	const git_index_entry *our_entry,
	const git_index_entry *their_entry)
{
	git_index_entry *entries[3] = { 0 };
	unsigned short i;
	int ret = 0;

	assert (index);

	if ((ancestor_entry &&
			(ret = index_entry_dup(&entries[0], index, ancestor_entry)) < 0) ||
		(our_entry &&
			(ret = index_entry_dup(&entries[1], index, our_entry)) < 0) ||
		(their_entry &&
			(ret = index_entry_dup(&entries[2], index, their_entry)) < 0))
		goto on_error;

	/* Validate entries */
	for (i = 0; i < 3; i++) {
		if (entries[i] && !valid_filemode(entries[i]->mode)) {
			git_error_set(GIT_ERROR_INDEX, "invalid filemode for stage %d entry",
				i + 1);
			ret = -1;
			goto on_error;
		}
	}

	/* Remove existing index entries for each path */
	for (i = 0; i < 3; i++) {
		if (entries[i] == NULL)
			continue;

		if ((ret = git_index_remove(index, entries[i]->path, 0)) != 0) {
			if (ret != GIT_ENOTFOUND)
				goto on_error;

			git_error_clear();
			ret = 0;
		}
	}

	/* Add the conflict entries */
	for (i = 0; i < 3; i++) {
		if (entries[i] == NULL)
			continue;

		/* Make sure stage is correct */
		GIT_INDEX_ENTRY_STAGE_SET(entries[i], i + 1);

		if ((ret = index_insert(index, &entries[i], 1, true, true, false)) < 0)
			goto on_error;

		entries[i] = NULL; /* don't free if later entry fails */
	}

	return 0;

on_error:
	for (i = 0; i < 3; i++) {
		if (entries[i] != NULL)
			index_entry_free(entries[i]);
	}

	return ret;
}