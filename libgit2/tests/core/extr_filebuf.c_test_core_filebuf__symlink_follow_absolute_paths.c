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
typedef  int /*<<< orphan*/  git_filebuf ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_filebuf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_path_supports_symlinks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_core_filebuf__symlink_follow_absolute_paths(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	git_buf source = GIT_BUF_INIT, target = GIT_BUF_INIT;

	if (!git_path_supports_symlinks(clar_sandbox_path()))
		cl_skip();

	cl_git_pass(git_buf_joinpath(&source, clar_sandbox_path(), "linkdir/link"));
	cl_git_pass(git_buf_joinpath(&target, clar_sandbox_path(), "linkdir/target"));
	cl_git_pass(p_mkdir("linkdir", 0777));
	cl_git_pass(p_symlink(target.ptr, source.ptr));

	cl_git_pass(git_filebuf_open(&file, source.ptr, 0, 0666));
	cl_git_pass(git_filebuf_printf(&file, "%s\n", "libgit2 rocks"));

	cl_assert_equal_i(true, git_path_exists("linkdir/target.lock"));

	cl_git_pass(git_filebuf_commit(&file));
	cl_assert_equal_i(true, git_path_exists("linkdir/target"));

	git_filebuf_cleanup(&file);
	git_buf_dispose(&source);
	git_buf_dispose(&target);

	cl_git_pass(git_futils_rmdir_r("linkdir", NULL, GIT_RMDIR_REMOVE_FILES));
}