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
 int GIT_EINVALIDSPEC ; 
 int git_branch_upstream (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_reference_dwim (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_is_branch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int retrieve_remote_tracking_reference(git_reference **base_ref, const char *identifier, git_repository *repo)
{
	git_reference *tracking, *ref;
	int error = -1;

	if (*base_ref == NULL) {
		if ((error = git_reference_dwim(&ref, repo, identifier)) < 0)
			return error;
	} else {
		ref = *base_ref;
		*base_ref = NULL;
	}

	if (!git_reference_is_branch(ref)) {
		error = GIT_EINVALIDSPEC;
		goto cleanup;
	}

	if ((error = git_branch_upstream(&tracking, ref)) < 0)
		goto cleanup;

	*base_ref = tracking;

cleanup:
	git_reference_free(ref);
	return error;
}