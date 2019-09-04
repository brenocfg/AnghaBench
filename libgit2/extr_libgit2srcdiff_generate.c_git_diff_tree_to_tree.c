#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_iterator_flag_t ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FROM_ITERATORS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GIT_DIFF_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_ITERATOR_IGNORE_CASE ; 
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  a_opts ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  b_opts ; 
 int /*<<< orphan*/  git_iterator_for_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_diff_tree_to_tree(
	git_diff **out,
	git_repository *repo,
	git_tree *old_tree,
	git_tree *new_tree,
	const git_diff_options *opts)
{
	git_diff *diff = NULL;
	git_iterator_flag_t iflag = GIT_ITERATOR_DONT_IGNORE_CASE;
	int error = 0;

	assert(out && repo);

	*out = NULL;

	/* for tree to tree diff, be case sensitive even if the index is
	 * currently case insensitive, unless the user explicitly asked
	 * for case insensitivity
	 */
	if (opts && (opts->flags & GIT_DIFF_IGNORE_CASE) != 0)
		iflag = GIT_ITERATOR_IGNORE_CASE;

	DIFF_FROM_ITERATORS(
		git_iterator_for_tree(&a, old_tree, &a_opts), iflag,
		git_iterator_for_tree(&b, new_tree, &b_opts), iflag
	);

	if (!error)
		*out = diff;

	return error;
}