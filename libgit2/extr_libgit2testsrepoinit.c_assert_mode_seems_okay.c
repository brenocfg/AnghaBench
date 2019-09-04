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
struct stat {int st_mode; } ;
typedef  int git_filemode_t ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_FOR_CORE_FILEMODE (int) ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_MODE_TYPE (int) ; 
 int GIT_PERMS_IS_EXEC (int) ; 
 int S_ISGID ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_i_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  git_path_lstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void assert_mode_seems_okay(
	const char *base, const char *path,
	git_filemode_t expect_mode, bool expect_setgid, bool core_filemode)
{
	git_buf full = GIT_BUF_INIT;
	struct stat st;

	cl_git_pass(git_buf_joinpath(&full, base, path));
	cl_git_pass(git_path_lstat(full.ptr, &st));
	git_buf_dispose(&full);

	if (!core_filemode) {
		CLEAR_FOR_CORE_FILEMODE(expect_mode);
		CLEAR_FOR_CORE_FILEMODE(st.st_mode);
		expect_setgid = false;
	}

	if (S_ISGID != 0)
		cl_assert_equal_b(expect_setgid, (st.st_mode & S_ISGID) != 0);

	cl_assert_equal_b(
		GIT_PERMS_IS_EXEC(expect_mode), GIT_PERMS_IS_EXEC(st.st_mode));

	cl_assert_equal_i_fmt(
		GIT_MODE_TYPE(expect_mode), GIT_MODE_TYPE(st.st_mode), "%07o");
}