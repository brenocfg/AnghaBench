#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_index_entry_is_conflict (int /*<<< orphan*/  const*) ; 
 size_t git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_index_get_byindex (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int merge_trivial_conflict_entrycount(git_index *index)
{
	const git_index_entry *entry;
	int count = 0;
	size_t i;

	for (i = 0; i < git_index_entrycount(index); i++) {
		cl_assert(entry = git_index_get_byindex(index, i));

		if (git_index_entry_is_conflict(entry))
			count++;
	}

	return count;
}