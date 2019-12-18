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
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_append2file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rename_helper(
	git_repository *repo, const char *from, const char *to, const char *extra)
{
	git_buf oldpath = GIT_BUF_INIT, newpath = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(
		&oldpath, git_repository_workdir(repo), from));
	cl_git_pass(git_buf_joinpath(
		&newpath, git_repository_workdir(repo), to));

	cl_git_pass(p_rename(oldpath.ptr, newpath.ptr));

	if (extra)
		cl_git_append2file(newpath.ptr, extra);

	git_buf_dispose(&oldpath);
	git_buf_dispose(&newpath);
}