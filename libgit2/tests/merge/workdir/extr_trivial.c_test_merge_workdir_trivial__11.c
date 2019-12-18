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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_index_get_bypath (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ git_index_reuc_entrycount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_trivial (char*,char*) ; 
 int merge_trivial_conflict_entrycount () ; 
 int /*<<< orphan*/  repo_index ; 

void test_merge_workdir_trivial__11(void)
{
	const git_index_entry *entry;

	cl_git_pass(merge_trivial("trivial-11", "trivial-11-branch"));

	cl_assert((entry = git_index_get_bypath(repo_index, "modified-in-both.txt", 0)) == NULL);
	cl_assert(git_index_reuc_entrycount(repo_index) == 0);

	cl_assert(merge_trivial_conflict_entrycount() == 3);
	cl_assert(entry = git_index_get_bypath(repo_index, "modified-in-both.txt", 1));
	cl_assert(entry = git_index_get_bypath(repo_index, "modified-in-both.txt", 2));
	cl_assert(entry = git_index_get_bypath(repo_index, "modified-in-both.txt", 3));
}