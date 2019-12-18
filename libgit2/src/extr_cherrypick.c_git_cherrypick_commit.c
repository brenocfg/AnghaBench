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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_merge_options ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int cherrypick_seterr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_parent (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int git_commit_parentcount (int /*<<< orphan*/ *) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_merge_trees (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

int git_cherrypick_commit(
	git_index **out,
	git_repository *repo,
	git_commit *cherrypick_commit,
	git_commit *our_commit,
	unsigned int mainline,
	const git_merge_options *merge_opts)
{
	git_commit *parent_commit = NULL;
	git_tree *parent_tree = NULL, *our_tree = NULL, *cherrypick_tree = NULL;
	int parent = 0, error = 0;

	assert(out && repo && cherrypick_commit && our_commit);

	if (git_commit_parentcount(cherrypick_commit) > 1) {
		if (!mainline)
			return cherrypick_seterr(cherrypick_commit,
				"mainline branch is not specified but %s is a merge commit");

		parent = mainline;
	} else {
		if (mainline)
			return cherrypick_seterr(cherrypick_commit,
				"mainline branch specified but %s is not a merge commit");

		parent = git_commit_parentcount(cherrypick_commit);
	}

	if (parent &&
		((error = git_commit_parent(&parent_commit, cherrypick_commit, (parent - 1))) < 0 ||
		(error = git_commit_tree(&parent_tree, parent_commit)) < 0))
		goto done;

	if ((error = git_commit_tree(&cherrypick_tree, cherrypick_commit)) < 0 ||
		(error = git_commit_tree(&our_tree, our_commit)) < 0)
		goto done;

	error = git_merge_trees(out, repo, parent_tree, our_tree, cherrypick_tree, merge_opts);

done:
	git_tree_free(parent_tree);
	git_tree_free(our_tree);
	git_tree_free(cherrypick_tree);
	git_commit_free(parent_commit);

	return error;
}