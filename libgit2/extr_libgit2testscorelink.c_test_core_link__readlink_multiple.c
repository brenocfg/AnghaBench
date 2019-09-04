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
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  do_symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_join (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,char*) ; 
 int p_readlink (char*,char*,int) ; 
 int /*<<< orphan*/  should_run () ; 

void test_core_link__readlink_multiple(void)
{
	git_buf target_path = GIT_BUF_INIT,
		path3 = GIT_BUF_INIT, path2 = GIT_BUF_INIT, path1 = GIT_BUF_INIT;
	int len;
	char buf[2048];

	if (!should_run())
		clar__skip();

	git_buf_join(&target_path, '/', clar_sandbox_path(), "readlink_final");
	git_buf_join(&path3, '/', clar_sandbox_path(), "readlink_3");
	git_buf_join(&path2, '/', clar_sandbox_path(), "readlink_2");
	git_buf_join(&path1, '/', clar_sandbox_path(), "readlink_1");

	do_symlink(git_buf_cstr(&target_path), git_buf_cstr(&path3), 0);
	do_symlink(git_buf_cstr(&path3), git_buf_cstr(&path2), 0);
	do_symlink(git_buf_cstr(&path2), git_buf_cstr(&path1), 0);

	len = p_readlink("readlink_1", buf, 2048);
	cl_must_pass(len);

	buf[len] = 0;

	cl_assert_equal_s(git_buf_cstr(&path2), buf);

	git_buf_dispose(&path1);
	git_buf_dispose(&path2);
	git_buf_dispose(&path3);
	git_buf_dispose(&target_path);
}