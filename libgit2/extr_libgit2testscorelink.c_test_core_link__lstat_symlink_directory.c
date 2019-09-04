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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  do_symlink (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_join (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  should_run () ; 

void test_core_link__lstat_symlink_directory(void)
{
	git_buf target_path = GIT_BUF_INIT;
	struct stat st;

	if (!should_run())
		clar__skip();

	git_buf_join(&target_path, '/', clar_sandbox_path(), "lstat_dirtarget");

	p_mkdir("lstat_dirtarget", 0777);
	do_symlink(git_buf_cstr(&target_path), "lstat_dirlink", 1);

	cl_must_pass(p_lstat("lstat_dirtarget", &st));
	cl_assert(S_ISDIR(st.st_mode));

	cl_must_pass(p_lstat("lstat_dirlink", &st));
	cl_assert(S_ISLNK(st.st_mode));
	cl_assert_equal_i(git_buf_len(&target_path), st.st_size);

	git_buf_dispose(&target_path);
}