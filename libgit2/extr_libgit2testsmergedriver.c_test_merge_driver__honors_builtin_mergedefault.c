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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_index_conflict_get (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  merge_branch () ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_merge_driver__honors_builtin_mergedefault(void)
{
	const git_index_entry *ancestor, *ours, *theirs;

	cl_repo_set_string(repo, "merge.default", "binary");
	merge_branch();

	cl_git_pass(git_index_conflict_get(&ancestor, &ours, &theirs,
		repo_index, "automergeable.txt"));
}