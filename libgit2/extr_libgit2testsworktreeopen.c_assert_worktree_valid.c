#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  gitdir; int /*<<< orphan*/  gitlink; int /*<<< orphan*/  workdir; int /*<<< orphan*/  is_worktree; } ;
typedef  TYPE_1__ git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_path (int,char const*,char*,...) ; 

__attribute__((used)) static void assert_worktree_valid(git_repository *wt, const char *parentdir, const char *wtdir)
{
	cl_assert(wt->is_worktree);

	cl_assert_equal_s(wt->workdir, cl_git_sandbox_path(1, wtdir, NULL));
	cl_assert_equal_s(wt->gitlink, cl_git_sandbox_path(0, wtdir, ".git", NULL));
	cl_assert_equal_s(wt->gitdir, cl_git_sandbox_path(1, parentdir, ".git", "worktrees", wtdir, NULL));
}