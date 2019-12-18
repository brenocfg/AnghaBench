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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int GIT_REPOSITORY_FOREACH_HEAD_SKIP_REPO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  branch_equals ; 
 int /*<<< orphan*/  git_reference_is_branch (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_reference_owner (int /*<<< orphan*/  const*) ; 
 int git_repository_foreach_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void*) ; 
 scalar_t__ git_repository_is_bare (int /*<<< orphan*/ *) ; 

int git_branch_is_checked_out(const git_reference *branch)
{
	git_repository *repo;
	int flags = 0;

	assert(branch);

	if (!git_reference_is_branch(branch))
		return 0;

	repo = git_reference_owner(branch);

	if (git_repository_is_bare(repo))
		flags |= GIT_REPOSITORY_FOREACH_HEAD_SKIP_REPO;

	return git_repository_foreach_head(repo, branch_equals, flags, (void *) branch) == 1;
}