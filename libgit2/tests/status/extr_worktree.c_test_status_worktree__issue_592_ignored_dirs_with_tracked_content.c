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
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  cb_status__count ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_status_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

void test_status_worktree__issue_592_ignored_dirs_with_tracked_content(void)
{
	int count = 0;
	git_repository *repo = cl_git_sandbox_init("issue_592b");

	cl_git_pass(git_status_foreach(repo, cb_status__count, &count));
	cl_assert_equal_i(1, count);

	/* if we are really mimicking core git, then only ignored1.txt
	 * at the top level will show up in the ignores list here.
	 * everything else will be unmodified or skipped completely.
	 */
}