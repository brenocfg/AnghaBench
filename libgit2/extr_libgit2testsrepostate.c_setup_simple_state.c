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
 int /*<<< orphan*/  _path ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_futils_mkpath2file (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_simple_state(const char *filename)
{
	cl_git_pass(git_buf_joinpath(&_path, git_repository_path(_repo), filename));
	git_futils_mkpath2file(git_buf_cstr(&_path), 0777);
	cl_git_mkfile(git_buf_cstr(&_path), "dummy");
}