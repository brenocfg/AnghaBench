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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_reflog_check_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_email ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_branch_move (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 

void test_refs_reflog_messages__moving_branch_default_message(void)
{
	git_reference *branch;
	git_reference *new_branch;
	git_oid id;

	cl_git_pass(git_reference_lookup(&branch, g_repo, "refs/heads/master"));
	git_oid_cpy(&id, git_reference_target(branch));
	cl_git_pass(git_branch_move(&new_branch, branch, "master2", 0));

	cl_reflog_check_entry(g_repo, git_reference_name(new_branch), 0,
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		g_email,
		"branch: renamed refs/heads/master to refs/heads/master2");

	git_reference_free(branch);
	git_reference_free(new_branch);
}