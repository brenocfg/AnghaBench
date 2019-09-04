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
 int /*<<< orphan*/ * a ; 
 int /*<<< orphan*/ * b ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  expect ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opts ; 
 void* resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void process_tree_to_tree_diffing(
	const char *old_commit,
	const char *new_commit)
{
	g_repo = cl_git_sandbox_init("unsymlinked.git");

	cl_assert((a = resolve_commit_oid_to_tree(g_repo, old_commit)) != NULL);
	cl_assert((b = resolve_commit_oid_to_tree(g_repo, new_commit)) != NULL);

	cl_git_pass(git_diff_tree_to_tree(&diff, g_repo, a, b, &opts));

	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, NULL, NULL, NULL, &expect));
}