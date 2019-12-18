#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  testfile ;
struct TYPE_8__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_setenv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * env_save ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  git_buf_rtruncate_at_char (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_path_prettify (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int git_path_root (char*) ; 
 int /*<<< orphan*/  git_sysdir_find_global_file (TYPE_1__*,char*) ; 
 char** home_values ; 
 scalar_t__ p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 
 int /*<<< orphan*/  set_global_search_path_from_env () ; 
 int /*<<< orphan*/  setenv_and_check (char*,char*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void test_core_env__0(void)
{
	git_buf path = GIT_BUF_INIT, found = GIT_BUF_INIT;
	char testfile[16], tidx = '0';
	char **val;
	const char *testname = "testfile";
	size_t testlen = strlen(testname);

	strncpy(testfile, testname, sizeof(testfile));
	cl_assert_equal_s(testname, testfile);

	for (val = home_values; *val != NULL; val++) {

		/* if we can't make the directory, let's just assume
		 * we are on a filesystem that doesn't support the
		 * characters in question and skip this test...
		 */
		if (p_mkdir(*val, 0777) != 0) {
			*val = ""; /* mark as not created */
			continue;
		}

		cl_git_pass(git_path_prettify(&path, *val, NULL));

		/* vary testfile name in each directory so accidentally leaving
		 * an environment variable set from a previous iteration won't
		 * accidentally make this test pass...
		 */
		testfile[testlen] = tidx++;
		cl_git_pass(git_buf_joinpath(&path, path.ptr, testfile));
		cl_git_mkfile(path.ptr, "find me");
		git_buf_rtruncate_at_char(&path, '/');

		cl_assert_equal_i(
			GIT_ENOTFOUND, git_sysdir_find_global_file(&found, testfile));

		setenv_and_check("HOME", path.ptr);
		set_global_search_path_from_env();

		cl_git_pass(git_sysdir_find_global_file(&found, testfile));

		cl_setenv("HOME", env_save[0]);
		set_global_search_path_from_env();

		cl_assert_equal_i(
			GIT_ENOTFOUND, git_sysdir_find_global_file(&found, testfile));

#ifdef GIT_WIN32
		setenv_and_check("HOMEDRIVE", NULL);
		setenv_and_check("HOMEPATH", NULL);
		setenv_and_check("USERPROFILE", path.ptr);
		set_global_search_path_from_env();

		cl_git_pass(git_sysdir_find_global_file(&found, testfile));

		{
			int root = git_path_root(path.ptr);
			char old;

			if (root >= 0) {
				setenv_and_check("USERPROFILE", NULL);
				set_global_search_path_from_env();

				cl_assert_equal_i(
					GIT_ENOTFOUND, git_sysdir_find_global_file(&found, testfile));

				old = path.ptr[root];
				path.ptr[root] = '\0';
				setenv_and_check("HOMEDRIVE", path.ptr);
				path.ptr[root] = old;
				setenv_and_check("HOMEPATH", &path.ptr[root]);
				set_global_search_path_from_env();

				cl_git_pass(git_sysdir_find_global_file(&found, testfile));
			}
		}
#endif

		(void)p_rmdir(*val);
	}

	git_buf_dispose(&path);
	git_buf_dispose(&found);
}