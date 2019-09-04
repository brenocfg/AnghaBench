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
struct TYPE_5__ {scalar_t__ ignore_case; } ;
typedef  TYPE_1__ git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FROM_ITERATORS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  a_opts ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  b_opts ; 
 int /*<<< orphan*/  git_diff__set_ignore_case (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_iterator_for_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

int git_diff_index_to_index(
	git_diff **out,
	git_repository *repo,
	git_index *old_index,
	git_index *new_index,
	const git_diff_options *opts)
{
	git_diff *diff;
	int error = 0;

	assert(out && old_index && new_index);

	*out = NULL;

	DIFF_FROM_ITERATORS(
		git_iterator_for_index(&a, repo, old_index, &a_opts), GIT_ITERATOR_DONT_IGNORE_CASE,
		git_iterator_for_index(&b, repo, new_index, &b_opts), GIT_ITERATOR_DONT_IGNORE_CASE
	);

	/* if index is in case-insensitive order, re-sort deltas to match */
	if (!error && (old_index->ignore_case || new_index->ignore_case))
		git_diff__set_ignore_case(diff, true);

	if (!error)
		*out = diff;

	return error;
}