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
typedef  int /*<<< orphan*/  git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_DONT_AUTOEXPAND ; 
 int /*<<< orphan*/  GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ diff_prepare_iterator_opts (char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int git_diff__from_iterators (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_diff_tree_to_workdir(
	git_diff **out,
	git_repository *repo,
	git_tree *old_tree,
	const git_diff_options *opts)
{
	git_iterator_options a_opts = GIT_ITERATOR_OPTIONS_INIT,
		b_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_iterator *a = NULL, *b = NULL;
	git_diff *diff = NULL;
	char *prefix = NULL;
	git_index *index;
	int error;

	assert(out && repo);

	*out = NULL;

	if ((error = diff_prepare_iterator_opts(&prefix, &a_opts, 0,
						&b_opts, GIT_ITERATOR_DONT_AUTOEXPAND, opts) < 0) ||
	    (error = git_repository_index__weakptr(&index, repo)) < 0 ||
	    (error = git_iterator_for_tree(&a, old_tree, &a_opts)) < 0 ||
	    (error = git_iterator_for_workdir(&b, repo, index, old_tree, &b_opts)) < 0 ||
	    (error = git_diff__from_iterators(&diff, repo, a, b, opts)) < 0)
		goto out;

	*out = diff;
	diff = NULL;
out:
	git_iterator_free(a);
	git_iterator_free(b);
	git_diff_free(diff);
	git__free(prefix);

	return error;
}