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
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_parent (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int match_with_parent(git_commit *commit, int i, git_diff_options *opts)
{
	git_commit *parent;
	git_tree *a, *b;
	git_diff *diff;
	int ndeltas;

	check_lg2(
		git_commit_parent(&parent, commit, (size_t)i), "Get parent", NULL);
	check_lg2(git_commit_tree(&a, parent), "Tree for parent", NULL);
	check_lg2(git_commit_tree(&b, commit), "Tree for commit", NULL);
	check_lg2(
		git_diff_tree_to_tree(&diff, git_commit_owner(commit), a, b, opts),
		"Checking diff between parent and commit", NULL);

	ndeltas = (int)git_diff_num_deltas(diff);

	git_diff_free(diff);
	git_tree_free(a);
	git_tree_free(b);
	git_commit_free(parent);

	return ndeltas > 0;
}