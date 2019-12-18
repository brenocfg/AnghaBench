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
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_path_supports_symlinks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 
 int /*<<< orphan*/  p_symlink (char*,char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_core_posix__unlink_removes_symlink(void)
{
	if (!git_path_supports_symlinks(clar_sandbox_path()))
		clar__skip();

	cl_git_mkfile("file", "Dummy file.");
	cl_git_pass(git_futils_mkdir("dir", 0777, 0));

	cl_must_pass(p_symlink("file", "file-symlink"));
	cl_must_pass(p_symlink("dir", "dir-symlink"));

	cl_must_pass(p_unlink("file-symlink"));
	cl_must_pass(p_unlink("dir-symlink"));

	cl_assert(git_path_exists("file"));
	cl_assert(git_path_exists("dir"));

	cl_must_pass(p_unlink("file"));
	cl_must_pass(p_rmdir("dir"));
}