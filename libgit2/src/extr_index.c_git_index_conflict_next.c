#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_index_entry ;
struct TYPE_7__ {scalar_t__ cur; TYPE_3__* index; } ;
typedef  TYPE_2__ git_index_conflict_iterator ;
struct TYPE_6__ {scalar_t__ length; } ;
struct TYPE_8__ {TYPE_1__ entries; } ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ git_index_entry_is_conflict (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_index_get_byindex (TYPE_3__*,scalar_t__) ; 
 int index_conflict__get_byindex (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,TYPE_3__*,scalar_t__) ; 

int git_index_conflict_next(
	const git_index_entry **ancestor_out,
	const git_index_entry **our_out,
	const git_index_entry **their_out,
	git_index_conflict_iterator *iterator)
{
	const git_index_entry *entry;
	int len;

	assert(ancestor_out && our_out && their_out && iterator);

	*ancestor_out = NULL;
	*our_out = NULL;
	*their_out = NULL;

	while (iterator->cur < iterator->index->entries.length) {
		entry = git_index_get_byindex(iterator->index, iterator->cur);

		if (git_index_entry_is_conflict(entry)) {
			if ((len = index_conflict__get_byindex(
				ancestor_out,
				our_out,
				their_out,
				iterator->index,
				iterator->cur)) < 0)
				return len;

			iterator->cur += len;
			return 0;
		}

		iterator->cur++;
	}

	return GIT_ITEROVER;
}