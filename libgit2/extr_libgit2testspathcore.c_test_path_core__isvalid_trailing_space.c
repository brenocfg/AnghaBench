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
 int /*<<< orphan*/  GIT_PATH_REJECT_TRAILING_SPACE ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isvalid (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_path_core__isvalid_trailing_space(void)
{
	cl_assert_equal_b(true, git_path_isvalid(NULL, "foo ", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "foo   ", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "foo/bar ", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, " ", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "foo /bar", 0, 0));

	cl_assert_equal_b(false, git_path_isvalid(NULL, "foo ", 0, GIT_PATH_REJECT_TRAILING_SPACE));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "foo   ", 0, GIT_PATH_REJECT_TRAILING_SPACE));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "foo/bar ", 0, GIT_PATH_REJECT_TRAILING_SPACE));
	cl_assert_equal_b(false, git_path_isvalid(NULL, " ", 0, GIT_PATH_REJECT_TRAILING_SPACE));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "foo /bar", 0, GIT_PATH_REJECT_TRAILING_SPACE));
}