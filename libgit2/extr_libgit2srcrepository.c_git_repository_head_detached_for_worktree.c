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
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 
 int git_repository_head_for_worktree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

int git_repository_head_detached_for_worktree(git_repository *repo, const char *name)
{
	git_reference *ref = NULL;
	int error;

	assert(repo && name);

	if ((error = git_repository_head_for_worktree(&ref, repo, name)) < 0)
		goto out;

	error = (git_reference_type(ref) != GIT_REFERENCE_SYMBOLIC);
out:
	git_reference_free(ref);

	return error;
}