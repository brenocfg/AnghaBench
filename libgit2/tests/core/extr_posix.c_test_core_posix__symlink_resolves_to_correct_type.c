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
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_path_supports_symlinks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 
 int /*<<< orphan*/  p_symlink (char*,char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_core_posix__symlink_resolves_to_correct_type(void)
{
	git_buf contents = GIT_BUF_INIT;

	if (!git_path_supports_symlinks(clar_sandbox_path()))
		clar__skip();

	cl_must_pass(git_futils_mkdir("dir", 0777, 0));
	cl_must_pass(git_futils_mkdir("file", 0777, 0));
	cl_git_mkfile("dir/file", "symlink target");

	cl_git_pass(p_symlink("file", "dir/link"));

	cl_git_pass(git_futils_readbuffer(&contents, "dir/file"));
	cl_assert_equal_s(contents.ptr, "symlink target");

	cl_must_pass(p_unlink("dir/link"));
	cl_must_pass(p_unlink("dir/file"));
	cl_must_pass(p_rmdir("dir"));
	cl_must_pass(p_rmdir("file"));

	git_buf_dispose(&contents);
}