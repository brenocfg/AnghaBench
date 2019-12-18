#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int git_merge__iterators (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int merge_indexes(
	git_index **out,
	git_repository *repo,
	git_tree *ancestor_tree,
	git_index *ours_index,
	git_index *theirs_index)
{
	git_iterator *ancestor = NULL, *ours = NULL, *theirs = NULL;
	git_iterator_options iter_opts = GIT_ITERATOR_OPTIONS_INIT;
	int error;

	iter_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

	if ((error = git_iterator_for_tree(&ancestor, ancestor_tree, &iter_opts)) < 0 ||
		(error = git_iterator_for_index(&ours, repo, ours_index, &iter_opts)) < 0 ||
		(error = git_iterator_for_index(&theirs, repo, theirs_index, &iter_opts)) < 0)
		goto done;

	error = git_merge__iterators(out, repo, ancestor, ours, theirs, NULL);

done:
	git_iterator_free(ancestor);
	git_iterator_free(ours);
	git_iterator_free(theirs);
	return error;
}