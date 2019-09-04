#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_EMPTY_HIERARCHY ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_tmp_dir ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 

void test_core_rmdir__fail_to_delete_non_empty_dir(void)
{
	git_buf file = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&file, empty_tmp_dir, "/two/file.txt"));

	cl_git_mkfile(git_buf_cstr(&file), "dummy");

	cl_git_fail(git_futils_rmdir_r(empty_tmp_dir, NULL, GIT_RMDIR_EMPTY_HIERARCHY));

	cl_must_pass(p_unlink(file.ptr));
	cl_git_pass(git_futils_rmdir_r(empty_tmp_dir, NULL, GIT_RMDIR_EMPTY_HIERARCHY));

	cl_assert(!git_path_exists(empty_tmp_dir));

	git_buf_dispose(&file);
}