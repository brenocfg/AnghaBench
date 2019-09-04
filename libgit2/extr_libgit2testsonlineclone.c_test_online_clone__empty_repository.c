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
 int GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  LIVE_EMPTYREPO_URL ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_options ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_unborn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_is_empty (int /*<<< orphan*/ ) ; 

void test_online_clone__empty_repository(void)
{
	git_reference *head;

	cl_git_pass(git_clone(&g_repo, LIVE_EMPTYREPO_URL, "./foo", &g_options));

	cl_assert_equal_i(true, git_repository_is_empty(g_repo));
	cl_assert_equal_i(true, git_repository_head_unborn(g_repo));

	cl_git_pass(git_reference_lookup(&head, g_repo, GIT_HEAD_FILE));
	cl_assert_equal_i(GIT_REFERENCE_SYMBOLIC, git_reference_type(head));
	cl_assert_equal_s("refs/heads/master", git_reference_symbolic_target(head));

	git_reference_free(head);
}