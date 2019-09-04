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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_NONE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_path_isfile (char*) ; 

void test_checkout_tree__doesnt_write_unrequested_files_to_worktree(void)
{
	git_oid master_oid;
	git_oid chomped_oid;
	git_commit* p_master_commit;
	git_commit* p_chomped_commit;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	git_oid_fromstr(&master_oid, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	git_oid_fromstr(&chomped_oid, "e90810b8df3e80c413d903f631643c716887138d");
	cl_git_pass(git_commit_lookup(&p_master_commit, g_repo, &master_oid));
	cl_git_pass(git_commit_lookup(&p_chomped_commit, g_repo, &chomped_oid));

	/* GIT_CHECKOUT_NONE should not add any file to the working tree from the
	 * index as it is supposed to be a dry run.
	 */
	opts.checkout_strategy = GIT_CHECKOUT_NONE;
	git_checkout_tree(g_repo, (git_object*)p_chomped_commit, &opts);
	cl_assert_equal_i(false, git_path_isfile("testrepo/readme.txt"));

	git_commit_free(p_master_commit);
	git_commit_free(p_chomped_commit);
}