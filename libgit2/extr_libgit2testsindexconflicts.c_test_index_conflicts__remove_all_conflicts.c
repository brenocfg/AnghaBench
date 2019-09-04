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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_conflict_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_entry_is_conflict (int /*<<< orphan*/  const*) ; 
 size_t git_index_entrycount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_index_get_byindex (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_index_has_conflicts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_index ; 

void test_index_conflicts__remove_all_conflicts(void)
{
	size_t i;
	const git_index_entry *entry;

	cl_assert(git_index_entrycount(repo_index) == 8);

	cl_assert_equal_i(true, git_index_has_conflicts(repo_index));

	git_index_conflict_cleanup(repo_index);

	cl_assert_equal_i(false, git_index_has_conflicts(repo_index));

	cl_assert(git_index_entrycount(repo_index) == 2);

	for (i = 0; i < git_index_entrycount(repo_index); i++) {
		cl_assert(entry = git_index_get_byindex(repo_index, i));
		cl_assert(!git_index_entry_is_conflict(entry));
	}
}