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
typedef  int /*<<< orphan*/  git_index_reuc_entry ;
typedef  int /*<<< orphan*/  git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int git_index_reuc_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_index_reuc_get_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  merge_trivial (int /*<<< orphan*/ **,char*,char*) ; 
 scalar_t__ merge_trivial_conflict_entrycount (int /*<<< orphan*/ *) ; 

void test_merge_trees_trivial__6(void)
{
	git_index *result;
	const git_index_entry *entry;
	const git_index_reuc_entry *reuc;

	cl_git_pass(merge_trivial(&result, "trivial-6", "trivial-6-branch"));

	cl_assert((entry = git_index_get_bypath(result, "removed-in-both.txt", 0)) == NULL);
	cl_assert(git_index_reuc_entrycount(result) == 1);
	cl_assert(reuc = git_index_reuc_get_bypath(result, "removed-in-both.txt"));

	cl_assert(merge_trivial_conflict_entrycount(result) == 0);

	git_index_free(result);
}