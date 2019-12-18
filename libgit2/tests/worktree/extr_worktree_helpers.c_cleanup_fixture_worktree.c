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
struct TYPE_3__ {scalar_t__ worktreename; scalar_t__ reponame; int /*<<< orphan*/ * worktree; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ worktree_fixture ;

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 

void cleanup_fixture_worktree(worktree_fixture *fixture)
{
	if (!fixture)
		return;

	if (fixture->repo) {
		git_repository_free(fixture->repo);
		fixture->repo = NULL;
	}
	if (fixture->worktree) {
		git_repository_free(fixture->worktree);
		fixture->worktree = NULL;
	}

	if (fixture->reponame)
		cl_fixture_cleanup(fixture->reponame);
	if (fixture->worktreename)
		cl_fixture_cleanup(fixture->worktreename);
}