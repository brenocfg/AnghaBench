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
struct TYPE_8__ {int flags; } ;
typedef  TYPE_1__ git_iterator ;
struct TYPE_9__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ git_index_entry ;

/* Variables and functions */
 int GIT_ITERATOR_IGNORE_CASE ; 
 int GIT_ITERATOR_INCLUDE_CONFLICTS ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  git_index_entry_is_conflict (TYPE_2__ const*) ; 
 int git_iterator_advance (TYPE_2__ const**,TYPE_1__*) ; 
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iterator_advance(
	const git_index_entry **entry,
	git_iterator *iterator)
{
	const git_index_entry *prev_entry = *entry;
	int cmp, error;

	/* if we're looking for conflicts, we only want to report
	 * one conflict for each file, instead of all three sides.
	 * so if this entry is a conflict for this file, and the
	 * previous one was a conflict for the same file, skip it.
	 */
	while ((error = git_iterator_advance(entry, iterator)) == 0) {
		if (!(iterator->flags & GIT_ITERATOR_INCLUDE_CONFLICTS) ||
			!git_index_entry_is_conflict(prev_entry) ||
			!git_index_entry_is_conflict(*entry))
			break;

		cmp = (iterator->flags & GIT_ITERATOR_IGNORE_CASE) ?
			strcasecmp(prev_entry->path, (*entry)->path) :
			strcmp(prev_entry->path, (*entry)->path);

		if (cmp)
			break;
	}

	if (error == GIT_ITEROVER) {
		*entry = NULL;
		error = 0;
	}

	return error;
}