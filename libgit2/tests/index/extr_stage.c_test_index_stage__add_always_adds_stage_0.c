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
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_index_entry_stage (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_index_find (size_t*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * git_index_get_byindex (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  repo_index ; 

void test_index_stage__add_always_adds_stage_0(void)
{
	size_t entry_idx;
	const git_index_entry *entry;

    cl_git_mkfile("./mergedrepo/new-file.txt", "new-file\n");

	cl_git_pass(git_index_add_bypath(repo_index, "new-file.txt"));

	cl_assert(!git_index_find(&entry_idx, repo_index, "new-file.txt"));
	cl_assert((entry = git_index_get_byindex(repo_index, entry_idx)) != NULL);
	cl_assert(git_index_entry_stage(entry) == 0);
}