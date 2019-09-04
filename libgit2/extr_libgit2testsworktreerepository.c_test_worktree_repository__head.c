#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_2__ {scalar_t__ repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ fixture ; 
 scalar_t__ git_reference_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,scalar_t__,char*) ; 
 scalar_t__ git_reference_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_for_worktree (int /*<<< orphan*/ **,scalar_t__,char*) ; 

void test_worktree_repository__head(void)
{
	git_reference *ref, *head;

	cl_git_pass(git_reference_lookup(&ref, fixture.repo, "refs/heads/testrepo-worktree"));
	cl_git_pass(git_repository_head_for_worktree(&head, fixture.repo, "testrepo-worktree"));
	cl_assert(git_reference_cmp(ref, head) == 0);
	cl_assert(git_reference_owner(ref) == fixture.repo);

	git_reference_free(ref);
	git_reference_free(head);
}