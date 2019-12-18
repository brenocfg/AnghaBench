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
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int merge_ancestor_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t) ; 

__attribute__((used)) static int merge_heads(
	git_annotated_commit **ancestor_head_out,
	git_annotated_commit **our_head_out,
	git_repository *repo,
	git_reference *our_ref,
	const git_annotated_commit **their_heads,
	size_t their_heads_len)
{
	git_annotated_commit *ancestor_head = NULL, *our_head = NULL;
	int error = 0;

	*ancestor_head_out = NULL;
	*our_head_out = NULL;

	if ((error = git_annotated_commit_from_ref(&our_head, repo, our_ref)) < 0)
		goto done;

	if ((error = merge_ancestor_head(&ancestor_head, repo, our_head, their_heads, their_heads_len)) < 0) {
		if (error != GIT_ENOTFOUND)
			goto done;

		git_error_clear();
		error = 0;
	}

	*ancestor_head_out = ancestor_head;
	*our_head_out = our_head;

done:
	if (error < 0) {
		git_annotated_commit_free(ancestor_head);
		git_annotated_commit_free(our_head);
	}

	return error;
}