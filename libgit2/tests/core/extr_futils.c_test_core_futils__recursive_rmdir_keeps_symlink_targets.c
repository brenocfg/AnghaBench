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
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git_futils_mkdir_r (char*,int) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_path_supports_symlinks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 
 int /*<<< orphan*/  p_symlink (char*,char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_core_futils__recursive_rmdir_keeps_symlink_targets(void)
{
	if (!git_path_supports_symlinks(clar_sandbox_path()))
		cl_skip();

	cl_git_pass(git_futils_mkdir_r("a/b", 0777));
	cl_git_pass(git_futils_mkdir_r("dir-target", 0777));
	cl_git_mkfile("dir-target/file", "Contents");
	cl_git_mkfile("file-target", "Contents");
	cl_must_pass(p_symlink("dir-target", "a/symlink"));
	cl_must_pass(p_symlink("file-target", "a/b/symlink"));

	cl_git_pass(git_futils_rmdir_r("a", NULL, GIT_RMDIR_REMOVE_FILES));

	cl_assert(git_path_exists("dir-target"));
	cl_assert(git_path_exists("file-target"));

	cl_must_pass(p_unlink("dir-target/file"));
	cl_must_pass(p_rmdir("dir-target"));
	cl_must_pass(p_unlink("file-target"));
}