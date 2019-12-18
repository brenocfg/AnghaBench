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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  cleanup_basic_dirs ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_futils_mkdir (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_mkdir_r (int /*<<< orphan*/ ,int) ; 
 int git_path_isdir (int /*<<< orphan*/ ) ; 

void test_core_mkdir__absolute(void)
{
	git_buf path = GIT_BUF_INIT;

	cl_set_cleanup(cleanup_basic_dirs, NULL);

	git_buf_joinpath(&path, clar_sandbox_path(), "d0");

	/* make a directory */
	cl_assert(!git_path_isdir(path.ptr));
	cl_git_pass(git_futils_mkdir(path.ptr, 0755, 0));
	cl_assert(git_path_isdir(path.ptr));

	git_buf_joinpath(&path, path.ptr, "subdir");
	cl_assert(!git_path_isdir(path.ptr));
	cl_git_pass(git_futils_mkdir(path.ptr, 0755, 0));
	cl_assert(git_path_isdir(path.ptr));

	/* ensure mkdir_r works for a single subdir */
	git_buf_joinpath(&path, path.ptr, "another");
	cl_assert(!git_path_isdir(path.ptr));
	cl_git_pass(git_futils_mkdir_r(path.ptr, 0755));
	cl_assert(git_path_isdir(path.ptr));

	/* ensure mkdir_r works */
	git_buf_joinpath(&path, clar_sandbox_path(), "d1/foo/bar/asdf");
	cl_assert(!git_path_isdir(path.ptr));
	cl_git_pass(git_futils_mkdir_r(path.ptr, 0755));
	cl_assert(git_path_isdir(path.ptr));

	/* ensure we don't imply recursive */
	git_buf_joinpath(&path, clar_sandbox_path(), "d2/foo/bar/asdf");
	cl_assert(!git_path_isdir(path.ptr));
	cl_git_fail(git_futils_mkdir(path.ptr, 0755, 0));
	cl_assert(!git_path_isdir(path.ptr));

	git_buf_dispose(&path);
}