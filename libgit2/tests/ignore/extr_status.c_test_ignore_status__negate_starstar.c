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
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_futils_mkdir_r (char*,int) ; 
 int /*<<< orphan*/  git_ignore_path_is_ignored (int*,int /*<<< orphan*/ ,char*) ; 

void test_ignore_status__negate_starstar(void)
{
    int ignored;

    g_repo = cl_git_sandbox_init("empty_standard_repo");

    cl_git_mkfile("empty_standard_repo/.gitignore",
              "code/projects/**/packages/*\n"
              "!code/projects/**/packages/repositories.config");

    cl_git_pass(git_futils_mkdir_r("empty_standard_repo/code/projects/foo/bar/packages", 0777));
    cl_git_mkfile("empty_standard_repo/code/projects/foo/bar/packages/repositories.config", "");

    cl_git_pass(git_ignore_path_is_ignored(&ignored, g_repo, "code/projects/foo/bar/packages/repositories.config"));
    cl_assert_equal_i(0, ignored);
}