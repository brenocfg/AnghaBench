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
struct TYPE_2__ {int /*<<< orphan*/  worktree; int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ fixture ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_worktree_refs__set_head_fails_when_worktree_wants_linked_repos_HEAD(void)
{
	git_reference *head;

	cl_git_pass(git_repository_head(&head, fixture.repo));
	cl_git_fail(git_repository_set_head(fixture.worktree, git_reference_name(head)));

	git_reference_free(head);
}