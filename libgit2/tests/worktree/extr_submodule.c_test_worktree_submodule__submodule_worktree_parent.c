#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int is_worktree; } ;
struct TYPE_6__ {TYPE_3__* worktree; TYPE_1__* repo; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/ * git_repository_path (TYPE_3__*) ; 
 int /*<<< orphan*/ * git_repository_workdir (TYPE_3__*) ; 
 TYPE_2__ parent ; 

void test_worktree_submodule__submodule_worktree_parent(void)
{
	cl_assert(git_repository_path(parent.worktree) != NULL);
	cl_assert(git_repository_workdir(parent.worktree) != NULL);

	cl_assert(!parent.repo->is_worktree);
	cl_assert(parent.worktree->is_worktree);
}