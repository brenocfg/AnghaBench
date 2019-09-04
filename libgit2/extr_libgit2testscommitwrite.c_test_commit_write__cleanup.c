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

/* Variables and functions */
 int /*<<< orphan*/  GIT_OPT_ENABLE_STRICT_OBJECT_CREATION ; 
 int /*<<< orphan*/ * branch ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * commit ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * head ; 
 int /*<<< orphan*/ * head_old ; 

void test_commit_write__cleanup(void)
{
	git_reference_free(head);
	head = NULL;

	git_reference_free(branch);
	branch = NULL;

	git_commit_free(commit);
	commit = NULL;

	git__free(head_old);
	head_old = NULL;

	cl_git_sandbox_cleanup();

	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_STRICT_OBJECT_CREATION, 1));
}