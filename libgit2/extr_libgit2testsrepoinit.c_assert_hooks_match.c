#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; int st_mode; } ;
typedef  int mode_t ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_FOR_CORE_FILEMODE (int) ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_FILEMODE_LINK ; 
 int GIT_MODE_TYPE (int) ; 
 int GIT_PERMS_FOR_WRITE (int) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i_fmt (int,int,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int g_umask ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  git_path_lstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void assert_hooks_match(
	const char *template_dir,
	const char *repo_dir,
	const char *hook_path,
	bool core_filemode)
{
	git_buf expected = GIT_BUF_INIT;
	git_buf actual = GIT_BUF_INIT;
	struct stat expected_st, st;

	cl_git_pass(git_buf_joinpath(&expected, template_dir, hook_path));
	cl_git_pass(git_path_lstat(expected.ptr, &expected_st));

	cl_git_pass(git_buf_joinpath(&actual, repo_dir, hook_path));
	cl_git_pass(git_path_lstat(actual.ptr, &st));

	cl_assert(expected_st.st_size == st.st_size);

	if (GIT_MODE_TYPE(expected_st.st_mode) != GIT_FILEMODE_LINK) {
		mode_t expected_mode =
			GIT_MODE_TYPE(expected_st.st_mode) |
			(GIT_PERMS_FOR_WRITE(expected_st.st_mode) & ~g_umask);

		if (!core_filemode) {
			CLEAR_FOR_CORE_FILEMODE(expected_mode);
			CLEAR_FOR_CORE_FILEMODE(st.st_mode);
		}

		cl_assert_equal_i_fmt(expected_mode, st.st_mode, "%07o");
	}

	git_buf_dispose(&expected);
	git_buf_dispose(&actual);
}