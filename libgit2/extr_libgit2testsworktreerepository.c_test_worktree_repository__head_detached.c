#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {TYPE_1__ target; } ;
typedef  TYPE_2__ git_reference ;
struct TYPE_9__ {int /*<<< orphan*/  repo; int /*<<< orphan*/  worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_6__ fixture ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_2__**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_head_detached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head_detached_for_worktree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_head_for_worktree (TYPE_2__**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_set_head_detached (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_worktree_repository__head_detached(void)
{
	git_reference *ref, *head;

	cl_git_pass(git_reference_lookup(&ref, fixture.repo, "refs/heads/testrepo-worktree"));
	cl_git_pass(git_repository_set_head_detached(fixture.worktree, &ref->target.oid));

	cl_assert(git_repository_head_detached(fixture.worktree));
	cl_assert(git_repository_head_detached_for_worktree(fixture.repo, "testrepo-worktree"));
	cl_git_fail(git_repository_head_for_worktree(&head, fixture.repo, "testrepo-worktree"));

	git_reference_free(ref);
}