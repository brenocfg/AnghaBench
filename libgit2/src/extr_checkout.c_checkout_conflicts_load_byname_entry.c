#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ theirs; scalar_t__ ours; scalar_t__ ancestor; } ;
typedef  TYPE_1__ git_index_name_entry ;
typedef  int /*<<< orphan*/  checkout_data ;
struct TYPE_10__ {int /*<<< orphan*/ * theirs; int /*<<< orphan*/ * ours; } ;
typedef  TYPE_2__ checkout_conflictdata ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 TYPE_2__* checkout_conflicts_search_ancestor (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* checkout_conflicts_search_branch (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int checkout_conflicts_load_byname_entry(
	checkout_conflictdata **ancestor_out,
	checkout_conflictdata **ours_out,
	checkout_conflictdata **theirs_out,
	checkout_data *data,
	const git_index_name_entry *name_entry)
{
	checkout_conflictdata *ancestor, *ours = NULL, *theirs = NULL;
	int error = 0;

	*ancestor_out = NULL;
	*ours_out = NULL;
	*theirs_out = NULL;

	if (!name_entry->ancestor) {
		git_error_set(GIT_ERROR_INDEX, "a NAME entry exists without an ancestor");
		error = -1;
		goto done;
	}

	if (!name_entry->ours && !name_entry->theirs) {
		git_error_set(GIT_ERROR_INDEX, "a NAME entry exists without an ours or theirs");
		error = -1;
		goto done;
	}

	if ((ancestor = checkout_conflicts_search_ancestor(data,
		name_entry->ancestor)) == NULL) {
		git_error_set(GIT_ERROR_INDEX,
			"a NAME entry referenced ancestor entry '%s' which does not exist in the main index",
			name_entry->ancestor);
		error = -1;
		goto done;
	}

	if (name_entry->ours) {
		if (strcmp(name_entry->ancestor, name_entry->ours) == 0)
			ours = ancestor;
		else if ((ours = checkout_conflicts_search_branch(data, name_entry->ours)) == NULL ||
			ours->ours == NULL) {
			git_error_set(GIT_ERROR_INDEX,
				"a NAME entry referenced our entry '%s' which does not exist in the main index",
				name_entry->ours);
			error = -1;
			goto done;
		}
	}

	if (name_entry->theirs) {
		if (strcmp(name_entry->ancestor, name_entry->theirs) == 0)
			theirs = ancestor;
		else if (name_entry->ours && strcmp(name_entry->ours, name_entry->theirs) == 0)
			theirs = ours;
		else if ((theirs = checkout_conflicts_search_branch(data, name_entry->theirs)) == NULL ||
			theirs->theirs == NULL) {
			git_error_set(GIT_ERROR_INDEX,
				"a NAME entry referenced their entry '%s' which does not exist in the main index",
				name_entry->theirs);
			error = -1;
			goto done;
		}
	}

	*ancestor_out = ancestor;
	*ours_out = ours;
	*theirs_out = theirs;

done:
	return error;
}