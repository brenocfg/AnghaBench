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
 int /*<<< orphan*/  CANCEL_VALUE ; 
 int /*<<< orphan*/  cancel_iteration ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_attrs ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*) ; 

void test_attr_repo__foreach(void)
{
	int count;

	count = 0;
	cl_git_pass(git_attr_foreach(
		g_repo, 0, "root_test1", &count_attrs, &count));
	cl_assert(count == 2);

	count = 0;
	cl_git_pass(git_attr_foreach(g_repo, 0, "sub/subdir_test1",
		&count_attrs, &count));
	cl_assert(count == 4); /* repoattr, rootattr, subattr, negattr */

	count = 0;
	cl_git_pass(git_attr_foreach(g_repo, 0, "sub/subdir_test2.txt",
		&count_attrs, &count));
	cl_assert(count == 6); /* repoattr, rootattr, subattr, reposub, negattr, another */

	count = 2;
	cl_assert_equal_i(
		CANCEL_VALUE, git_attr_foreach(
			g_repo, 0, "sub/subdir_test1", &cancel_iteration, &count)
	);
}