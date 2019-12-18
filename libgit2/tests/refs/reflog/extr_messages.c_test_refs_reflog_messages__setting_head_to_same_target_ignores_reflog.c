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
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 
 size_t reflog_entrycount (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_refs_reflog_messages__setting_head_to_same_target_ignores_reflog(void)
{
	size_t nentries, nentries_after;

	nentries = reflog_entrycount(g_repo, GIT_HEAD_FILE);

	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/haacked"));
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/haacked"));

	nentries_after = reflog_entrycount(g_repo, GIT_HEAD_FILE);

	cl_assert_equal_i(nentries + 1, nentries_after);
}