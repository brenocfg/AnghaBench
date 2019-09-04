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
struct merge_name_entry {int dummy; } ;
typedef  int /*<<< orphan*/  git_index_name_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 size_t git_index_name_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_index_name_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  name_entry_eq_merge_name_entry (struct merge_name_entry const*,int /*<<< orphan*/  const*) ; 

int merge_test_names(git_index *index, const struct merge_name_entry expected[], size_t expected_len)
{
	size_t i;
	const git_index_name_entry *name_entry;

	/*
	dump_names(index);
	*/

	if (git_index_name_entrycount(index) != expected_len)
		return 0;

	for (i = 0; i < expected_len; i++) {
		if ((name_entry = git_index_name_get_byindex(index, i)) == NULL)
			return 0;

		if (! name_entry_eq_merge_name_entry(&expected[i], name_entry))
			return 0;
	}

	return 1;
}