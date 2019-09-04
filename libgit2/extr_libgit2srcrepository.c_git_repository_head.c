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
 int GIT_ENOTFOUND ; 
 int GIT_EUNBORNBRANCH ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_reference_lookup_resolved (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 

int git_repository_head(git_reference **head_out, git_repository *repo)
{
	git_reference *head;
	int error;

	assert(head_out);

	if ((error = git_reference_lookup(&head, repo, GIT_HEAD_FILE)) < 0)
		return error;

	if (git_reference_type(head) == GIT_REFERENCE_DIRECT) {
		*head_out = head;
		return 0;
	}

	error = git_reference_lookup_resolved(head_out, repo, git_reference_symbolic_target(head), -1);
	git_reference_free(head);

	return error == GIT_ENOTFOUND ? GIT_EUNBORNBRANCH : error;
}