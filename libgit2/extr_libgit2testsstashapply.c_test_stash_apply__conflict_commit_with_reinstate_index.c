#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_stash_apply_options ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 TYPE_1__ GIT_STASH_APPLY_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_STASH_APPLY_REINSTATE_INDEX ; 
 int /*<<< orphan*/  GIT_STATUS_CURRENT ; 
 int /*<<< orphan*/  GIT_STATUS_INDEX_MODIFIED ; 
 int /*<<< orphan*/  GIT_STATUS_INDEX_NEW ; 
 int /*<<< orphan*/  GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  assert_status (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_repo_commit_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_conflict_get (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_has_conflicts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 
 int /*<<< orphan*/  signature ; 

void test_stash_apply__conflict_commit_with_reinstate_index(void)
{
	git_stash_apply_options opts = GIT_STASH_APPLY_OPTIONS_INIT;
	const git_index_entry *ancestor;
	const git_index_entry *our;
	const git_index_entry *their;

	opts.flags = GIT_STASH_APPLY_REINSTATE_INDEX;

	cl_git_rewritefile("stash/what", "ciao\n");
	cl_git_pass(git_index_add_bypath(repo_index, "what"));
	cl_repo_commit_from_index(NULL, repo, signature, 0, "Other commit");

	cl_git_pass(git_stash_apply(repo, 0, &opts));

	cl_assert_equal_i(git_index_has_conflicts(repo_index), 1);
	cl_git_pass(git_index_conflict_get(&ancestor, &our, &their, repo_index, "what")); /* unmerged */
	assert_status(repo, "how", GIT_STATUS_CURRENT);
	assert_status(repo, "who", GIT_STATUS_INDEX_MODIFIED);
	assert_status(repo, "when", GIT_STATUS_WT_NEW);
	assert_status(repo, "why", GIT_STATUS_INDEX_NEW);
}