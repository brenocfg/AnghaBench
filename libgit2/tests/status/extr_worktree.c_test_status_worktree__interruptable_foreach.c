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
 int /*<<< orphan*/  cb_status__interrupt ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int git_status_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

void test_status_worktree__interruptable_foreach(void)
{
	int count = 0;
	git_repository *repo = cl_git_sandbox_init("status");

	cl_assert_equal_i(
		-111, git_status_foreach(repo, cb_status__interrupt, &count)
	);

	cl_assert_equal_i(8, count);
}