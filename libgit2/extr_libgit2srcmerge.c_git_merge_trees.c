#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ git_merge_options ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 TYPE_2__ GIT_ITERATOR_OPTIONS_INIT ; 
 int GIT_MERGE_SKIP_REUC ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_index_new (int /*<<< orphan*/ **) ; 
 int git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int git_merge__iterators (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  git_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_tree_id (int /*<<< orphan*/  const*) ; 

int git_merge_trees(
	git_index **out,
	git_repository *repo,
	const git_tree *ancestor_tree,
	const git_tree *our_tree,
	const git_tree *their_tree,
	const git_merge_options *merge_opts)
{
	git_iterator *ancestor_iter = NULL, *our_iter = NULL, *their_iter = NULL;
	git_iterator_options iter_opts = GIT_ITERATOR_OPTIONS_INIT;
	int error;

	assert(out && repo);

	/* if one side is treesame to the ancestor, take the other side */
	if (ancestor_tree && merge_opts && (merge_opts->flags & GIT_MERGE_SKIP_REUC)) {
		const git_tree *result = NULL;
		const git_oid *ancestor_tree_id = git_tree_id(ancestor_tree);

		if (our_tree && !git_oid_cmp(ancestor_tree_id, git_tree_id(our_tree)))
			result = their_tree;
		else if (their_tree && !git_oid_cmp(ancestor_tree_id, git_tree_id(their_tree)))
			result = our_tree;

		if (result) {
			if ((error = git_index_new(out)) == 0)
    			error = git_index_read_tree(*out, result);

			return error;
		}
	}

	iter_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

	if ((error = git_iterator_for_tree(
			&ancestor_iter, (git_tree *)ancestor_tree, &iter_opts)) < 0 ||
		(error = git_iterator_for_tree(
			&our_iter, (git_tree *)our_tree, &iter_opts)) < 0 ||
		(error = git_iterator_for_tree(
			&their_iter, (git_tree *)their_tree, &iter_opts)) < 0)
		goto done;

	error = git_merge__iterators(
		out, repo, ancestor_iter, our_iter, their_iter, merge_opts);

done:
	git_iterator_free(ancestor_iter);
	git_iterator_free(our_iter);
	git_iterator_free(their_iter);

	return error;
}