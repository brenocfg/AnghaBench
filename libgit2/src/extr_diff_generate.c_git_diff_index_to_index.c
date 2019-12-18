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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_5__ {scalar_t__ ignore_case; } ;
typedef  TYPE_1__ git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ diff_prepare_iterator_opts (char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int git_diff__from_iterators (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_diff__set_ignore_case (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 

int git_diff_index_to_index(
	git_diff **out,
	git_repository *repo,
	git_index *old_index,
	git_index *new_index,
	const git_diff_options *opts)
{
	git_iterator_options a_opts = GIT_ITERATOR_OPTIONS_INIT,
		b_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_iterator *a = NULL, *b = NULL;
	git_diff *diff = NULL;
	char *prefix = NULL;
	int error;

	assert(out && old_index && new_index);

	*out = NULL;

	if ((error = diff_prepare_iterator_opts(&prefix, &a_opts, GIT_ITERATOR_DONT_IGNORE_CASE,
						&b_opts, GIT_ITERATOR_DONT_IGNORE_CASE, opts) < 0) ||
	    (error = git_iterator_for_index(&a, repo, old_index, &a_opts)) < 0 ||
	    (error = git_iterator_for_index(&b, repo, new_index, &b_opts)) < 0 ||
	    (error = git_diff__from_iterators(&diff, repo, a, b, opts)) < 0)
		goto out;

	/* if index is in case-insensitive order, re-sort deltas to match */
	if (old_index->ignore_case || new_index->ignore_case)
		git_diff__set_ignore_case(diff, true);

	*out = diff;
	diff = NULL;
out:
	git_iterator_free(a);
	git_iterator_free(b);
	git_diff_free(diff);
	git__free(prefix);

	return error;
}