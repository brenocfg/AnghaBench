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
typedef  int /*<<< orphan*/  git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_filebuf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_path_supports_symlinks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char const*,int) ; 
 int /*<<< orphan*/  p_symlink (char*,char const*) ; 

void test_core_filebuf__symlink_follow(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	const char *dir = "linkdir", *source = "linkdir/link";

	if (!git_path_supports_symlinks(clar_sandbox_path()))
		cl_skip();

	cl_git_pass(p_mkdir(dir, 0777));
	cl_git_pass(p_symlink("target", source));

	cl_git_pass(git_filebuf_open(&file, source, 0, 0666));
	cl_git_pass(git_filebuf_printf(&file, "%s\n", "libgit2 rocks"));

	cl_assert_equal_i(true, git_path_exists("linkdir/target.lock"));

	cl_git_pass(git_filebuf_commit(&file));
	cl_assert_equal_i(true, git_path_exists("linkdir/target"));

	git_filebuf_cleanup(&file);

	/* The second time around, the target file does exist */
	cl_git_pass(git_filebuf_open(&file, source, 0, 0666));
	cl_git_pass(git_filebuf_printf(&file, "%s\n", "libgit2 rocks"));

	cl_assert_equal_i(true, git_path_exists("linkdir/target.lock"));

	cl_git_pass(git_filebuf_commit(&file));
	cl_assert_equal_i(true, git_path_exists("linkdir/target"));

	git_filebuf_cleanup(&file);
	cl_git_pass(git_futils_rmdir_r(dir, NULL, GIT_RMDIR_REMOVE_FILES));
}