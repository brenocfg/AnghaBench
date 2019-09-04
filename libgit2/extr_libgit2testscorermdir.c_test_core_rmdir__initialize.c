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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_tmp_dir ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  p_mkdir (int /*<<< orphan*/ ,int) ; 

void test_core_rmdir__initialize(void)
{
	git_buf path = GIT_BUF_INIT;

	cl_must_pass(p_mkdir(empty_tmp_dir, 0777));

	cl_git_pass(git_buf_joinpath(&path, empty_tmp_dir, "/one"));
	cl_must_pass(p_mkdir(path.ptr, 0777));

	cl_git_pass(git_buf_joinpath(&path, empty_tmp_dir, "/one/two_one"));
	cl_must_pass(p_mkdir(path.ptr, 0777));

	cl_git_pass(git_buf_joinpath(&path, empty_tmp_dir, "/one/two_two"));
	cl_must_pass(p_mkdir(path.ptr, 0777));

	cl_git_pass(git_buf_joinpath(&path, empty_tmp_dir, "/one/two_two/three"));
	cl_must_pass(p_mkdir(path.ptr, 0777));

	cl_git_pass(git_buf_joinpath(&path, empty_tmp_dir, "/two"));
	cl_must_pass(p_mkdir(path.ptr, 0777));

	git_buf_dispose(&path);
}