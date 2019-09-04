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

/* Variables and functions */
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_reflog_check_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int /*<<< orphan*/  git_repository_detach_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head_detached (int /*<<< orphan*/ ) ; 

void test_refs_reflog_messages__detaching_head_default_message(void)
{
	git_reference *ref;

	cl_assert_equal_i(false, git_repository_head_detached(g_repo));

	cl_git_pass(git_repository_detach_head(g_repo));
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		NULL, "checkout: moving from master to a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	cl_assert_equal_i(true, git_repository_head_detached(g_repo));

	/* take the repo back to its original state */
	cl_git_pass(git_reference_symbolic_create(&ref, g_repo, "HEAD", "refs/heads/master",
											  true, "REATTACH"));

	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		NULL, "REATTACH");

	cl_assert_equal_i(false, git_repository_head_detached(g_repo));

	git_reference_free(ref);
}