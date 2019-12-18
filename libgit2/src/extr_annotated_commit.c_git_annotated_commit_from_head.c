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
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_annotated_commit_from_head(
	git_annotated_commit **out,
	git_repository *repo)
{
	git_reference *head;
	int error;

	assert(out && repo);

	*out = NULL;

    if ((error = git_reference_lookup(&head, repo, GIT_HEAD_FILE)) < 0)
		return -1;

	error = git_annotated_commit_from_ref(out, repo, head);

	git_reference_free(head);
	return error;
}