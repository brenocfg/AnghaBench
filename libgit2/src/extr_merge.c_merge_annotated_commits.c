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
typedef  int /*<<< orphan*/  git_merge_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int compute_base (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int git_merge__iterators (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int iterator_for_annotated_commit (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int merge_annotated_commits(
	git_index **index_out,
	git_annotated_commit **base_out,
	git_repository *repo,
	git_annotated_commit *ours,
	git_annotated_commit *theirs,
	size_t recursion_level,
	const git_merge_options *opts)
{
	git_annotated_commit *base = NULL;
	git_iterator *base_iter = NULL, *our_iter = NULL, *their_iter = NULL;
	int error;

	if ((error = compute_base(&base, repo, ours, theirs, opts,
		recursion_level)) < 0) {

		if (error != GIT_ENOTFOUND)
			goto done;

		git_error_clear();
	}

	if ((error = iterator_for_annotated_commit(&base_iter, base)) < 0 ||
		(error = iterator_for_annotated_commit(&our_iter, ours)) < 0 ||
		(error = iterator_for_annotated_commit(&their_iter, theirs)) < 0 ||
		(error = git_merge__iterators(index_out, repo, base_iter, our_iter,
			their_iter, opts)) < 0)
		goto done;

	if (base_out) {
		*base_out = base;
		base = NULL;
	}

done:
	git_annotated_commit_free(base);
	git_iterator_free(base_iter);
	git_iterator_free(our_iter);
	git_iterator_free(their_iter);
	return error;
}