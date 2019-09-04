#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_7__ {int /*<<< orphan*/ * worktree; } ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 TYPE_4__ child ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_discover (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 

void test_worktree_submodule__open_discovered_submodule_worktree(void)
{
	git_buf path = GIT_BUF_INIT;
	git_repository *repo;

	cl_git_pass(git_repository_discover(&path,
		git_repository_workdir(child.worktree), false, NULL));
	cl_git_pass(git_repository_open(&repo, path.ptr));
	cl_assert_equal_s(git_repository_workdir(child.worktree),
		git_repository_workdir(repo));

	git_buf_dispose(&path);
	git_repository_free(repo);
}