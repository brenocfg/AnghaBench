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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_setenv (char*,char*) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_sysdir_find_global_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_sysdir_find_system_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_global_search_path_from_env () ; 
 int /*<<< orphan*/  set_system_search_path_from_env () ; 

void test_core_env__1(void)
{
	git_buf path = GIT_BUF_INIT;

	cl_assert_equal_i(
		GIT_ENOTFOUND, git_sysdir_find_global_file(&path, "nonexistentfile"));

	cl_git_pass(cl_setenv("HOME", "doesnotexist"));
#ifdef GIT_WIN32
	cl_git_pass(cl_setenv("HOMEPATH", "doesnotexist"));
	cl_git_pass(cl_setenv("USERPROFILE", "doesnotexist"));
#endif
	set_global_search_path_from_env();

	cl_assert_equal_i(
		GIT_ENOTFOUND, git_sysdir_find_global_file(&path, "nonexistentfile"));

	cl_git_pass(cl_setenv("HOME", NULL));
#ifdef GIT_WIN32
	cl_git_pass(cl_setenv("HOMEPATH", NULL));
	cl_git_pass(cl_setenv("USERPROFILE", NULL));
#endif
	set_global_search_path_from_env();
	set_system_search_path_from_env();

	cl_assert_equal_i(
		GIT_ENOTFOUND, git_sysdir_find_global_file(&path, "nonexistentfile"));

	cl_assert_equal_i(
		GIT_ENOTFOUND, git_sysdir_find_system_file(&path, "nonexistentfile"));

#ifdef GIT_WIN32
	cl_git_pass(cl_setenv("PROGRAMFILES", NULL));
	set_system_search_path_from_env();

	cl_assert_equal_i(
		GIT_ENOTFOUND, git_sysdir_find_system_file(&path, "nonexistentfile"));
#endif

	git_buf_dispose(&path);
}