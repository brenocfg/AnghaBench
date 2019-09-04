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
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FROM_ITERATORS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_ITERATOR_DONT_AUTOEXPAND ; 
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  a_opts ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  b_opts ; 
 int /*<<< orphan*/  git_iterator_for_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_diff_tree_to_workdir(
	git_diff **out,
	git_repository *repo,
	git_tree *old_tree,
	const git_diff_options *opts)
{
	git_diff *diff = NULL;
	git_index *index;
	int error = 0;

	assert(out && repo);

	*out = NULL;

	if ((error = git_repository_index__weakptr(&index, repo)))
		return error;

	DIFF_FROM_ITERATORS(
		git_iterator_for_tree(&a, old_tree, &a_opts), 0,
		git_iterator_for_workdir(&b, repo, index, old_tree, &b_opts), GIT_ITERATOR_DONT_AUTOEXPAND
	);

	if (!error)
		*out = diff;

	return error;
}