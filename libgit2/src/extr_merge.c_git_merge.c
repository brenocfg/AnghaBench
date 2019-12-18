#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_merge_options ;
typedef  int /*<<< orphan*/  git_indexwriter ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_6__ {unsigned int checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 unsigned int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_ERROR_MERGE ; 
 int /*<<< orphan*/  GIT_INDEXWRITER_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int git_annotated_commit_from_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_checkout_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_index_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_indexwriter_cleanup (int /*<<< orphan*/ *) ; 
 int git_indexwriter_commit (int /*<<< orphan*/ *) ; 
 int git_indexwriter_init_for_operation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 int git_merge__append_conflicts_to_merge_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_merge__check_result (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_merge__setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int merge_annotated_commits (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int merge_normalize_checkout_opts (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__ const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t) ; 
 int /*<<< orphan*/  merge_state_cleanup (int /*<<< orphan*/ *) ; 

int git_merge(
	git_repository *repo,
	const git_annotated_commit **their_heads,
	size_t their_heads_len,
	const git_merge_options *merge_opts,
	const git_checkout_options *given_checkout_opts)
{
	git_reference *our_ref = NULL;
	git_checkout_options checkout_opts;
	git_annotated_commit *our_head = NULL, *base = NULL;
	git_index *repo_index = NULL, *index = NULL;
	git_indexwriter indexwriter = GIT_INDEXWRITER_INIT;
	unsigned int checkout_strategy;
	int error = 0;

	assert(repo && their_heads && their_heads_len > 0);

	if (their_heads_len != 1) {
		git_error_set(GIT_ERROR_MERGE, "can only merge a single branch");
		return -1;
	}

	if ((error = git_repository__ensure_not_bare(repo, "merge")) < 0)
		goto done;

	checkout_strategy = given_checkout_opts ?
		given_checkout_opts->checkout_strategy :
		GIT_CHECKOUT_SAFE;

	if ((error = git_indexwriter_init_for_operation(&indexwriter, repo,
		&checkout_strategy)) < 0)
		goto done;

	if ((error = git_repository_index(&repo_index, repo) < 0) ||
	    (error = git_index_read(repo_index, 0) < 0))
		goto done;

	/* Write the merge setup files to the repository. */
	if ((error = git_annotated_commit_from_head(&our_head, repo)) < 0 ||
		(error = git_merge__setup(repo, our_head, their_heads,
			their_heads_len)) < 0)
		goto done;

	/* TODO: octopus */

	if ((error = merge_annotated_commits(&index, &base, repo, our_head,
			(git_annotated_commit *)their_heads[0], 0, merge_opts)) < 0 ||
		(error = git_merge__check_result(repo, index)) < 0 ||
		(error = git_merge__append_conflicts_to_merge_msg(repo, index)) < 0)
		goto done;

	/* check out the merge results */

	if ((error = merge_normalize_checkout_opts(&checkout_opts, repo,
			given_checkout_opts, checkout_strategy,
			base, our_head, their_heads, their_heads_len)) < 0 ||
		(error = git_checkout_index(repo, index, &checkout_opts)) < 0)
		goto done;

	error = git_indexwriter_commit(&indexwriter);

done:
	if (error < 0)
		merge_state_cleanup(repo);

	git_indexwriter_cleanup(&indexwriter);
	git_index_free(index);
	git_annotated_commit_free(our_head);
	git_annotated_commit_free(base);
	git_reference_free(our_ref);
	git_index_free(repo_index);

	return error;
}