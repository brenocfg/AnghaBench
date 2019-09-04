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
 int /*<<< orphan*/  GIT_PATH_REJECT_DOS_PATHS ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isvalid (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_path_core__isvalid_dos_paths(void)
{
	cl_assert_equal_b(true, git_path_isvalid(NULL, "aux", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "aux.", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "aux:", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "aux.asdf", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "aux.asdf\\zippy", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "aux:asdf\\foobar", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "con", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "prn", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "nul", 0, 0));

	cl_assert_equal_b(false, git_path_isvalid(NULL, "aux", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "aux.", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "aux:", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "aux.asdf", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "aux.asdf\\zippy", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "aux:asdf\\foobar", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "con", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "prn", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(false, git_path_isvalid(NULL, "nul", 0, GIT_PATH_REJECT_DOS_PATHS));

	cl_assert_equal_b(true, git_path_isvalid(NULL, "aux1", 0, 0));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "aux1", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "auxn", 0, GIT_PATH_REJECT_DOS_PATHS));
	cl_assert_equal_b(true, git_path_isvalid(NULL, "aux\\foo", 0, GIT_PATH_REJECT_DOS_PATHS));
}