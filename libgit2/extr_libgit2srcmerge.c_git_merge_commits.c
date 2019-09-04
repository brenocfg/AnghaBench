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
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int git_annotated_commit_from_commit (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int merge_annotated_commits (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int git_merge_commits(
	git_index **out,
	git_repository *repo,
	const git_commit *our_commit,
	const git_commit *their_commit,
	const git_merge_options *opts)
{
	git_annotated_commit *ours = NULL, *theirs = NULL, *base = NULL;
	int error = 0;

	if ((error = git_annotated_commit_from_commit(&ours, (git_commit *)our_commit)) < 0 ||
		(error = git_annotated_commit_from_commit(&theirs, (git_commit *)their_commit)) < 0)
		goto done;

	error = merge_annotated_commits(out, &base, repo, ours, theirs, 0, opts);

done:
	git_annotated_commit_free(ours);
	git_annotated_commit_free(theirs);
	git_annotated_commit_free(base);
	return error;
}