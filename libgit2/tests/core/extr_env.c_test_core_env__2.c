#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  testfile ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  check_global_searchpath (int /*<<< orphan*/ ,int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_rtruncate_at_char (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_path_prettify (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_sysdir_find_global_file (TYPE_1__*,char*) ; 
 char** home_values ; 
 scalar_t__ p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void test_core_env__2(void)
{
	git_buf path = GIT_BUF_INIT, found = GIT_BUF_INIT;
	char testfile[16], tidx = '0';
	char **val;
	const char *testname = "alternate";
	size_t testlen = strlen(testname);

	strncpy(testfile, testname, sizeof(testfile));
	cl_assert_equal_s(testname, testfile);

	for (val = home_values; *val != NULL; val++) {

		/* if we can't make the directory, let's just assume
		 * we are on a filesystem that doesn't support the
		 * characters in question and skip this test...
		 */
		if (p_mkdir(*val, 0777) != 0 && errno != EEXIST) {
			*val = ""; /* mark as not created */
			continue;
		}

		cl_git_pass(git_path_prettify(&path, *val, NULL));

		/* vary testfile name so any sloppiness is resetting variables or
		 * deleting files won't accidentally make a test pass.
		 */
		testfile[testlen] = tidx++;
		cl_git_pass(git_buf_joinpath(&path, path.ptr, testfile));
		cl_git_mkfile(path.ptr, "find me");
		git_buf_rtruncate_at_char(&path, '/');

		/* default should be NOTFOUND */
		cl_assert_equal_i(
			GIT_ENOTFOUND, git_sysdir_find_global_file(&found, testfile));

		/* try plain, append $PATH, and prepend $PATH */
		check_global_searchpath(path.ptr,  0, testfile, &found);
		check_global_searchpath(path.ptr, -1, testfile, &found);
		check_global_searchpath(path.ptr,  1, testfile, &found);

		/* cleanup */
		cl_git_pass(git_buf_joinpath(&path, path.ptr, testfile));
		(void)p_unlink(path.ptr);
		(void)p_rmdir(*val);
	}

	git_buf_dispose(&path);
	git_buf_dispose(&found);
}