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
 unsigned int GIT_SUBMODULE_STATUS_IN_CONFIG ; 
 unsigned int GIT_SUBMODULE_STATUS_IN_HEAD ; 
 unsigned int GIT_SUBMODULE_STATUS_IN_INDEX ; 
 unsigned int GIT_SUBMODULE_STATUS_IN_WD ; 
 int GIT_SUBMODULE_STATUS_IS_UNMODIFIED (unsigned int) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_append2file (char*,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 unsigned int get_submodule_status (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_futils_mkdir_relative (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_submodule_status__untracked_dirs_containing_ignored_files(void)
{
	unsigned int status, expected;

	cl_git_append2file(
		"submod2/.git/modules/sm_unchanged/info/exclude", "\n*.ignored\n");

	cl_git_pass(
		git_futils_mkdir_relative("sm_unchanged/directory", "submod2", 0755, 0, NULL));
	cl_git_mkfile(
		"submod2/sm_unchanged/directory/i_am.ignored",
		"ignore this file, please\n");

	status = get_submodule_status(g_repo, "sm_unchanged");
	cl_assert(GIT_SUBMODULE_STATUS_IS_UNMODIFIED(status));

	expected = GIT_SUBMODULE_STATUS_IN_HEAD |
		GIT_SUBMODULE_STATUS_IN_INDEX |
		GIT_SUBMODULE_STATUS_IN_CONFIG |
		GIT_SUBMODULE_STATUS_IN_WD;
	cl_assert(status == expected);
}