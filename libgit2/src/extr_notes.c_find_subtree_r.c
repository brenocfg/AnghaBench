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

/* Variables and functions */
 int GIT_EEXISTS ; 
 int find_subtree_in_current_level (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_id (int /*<<< orphan*/ *) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_subtree_r(git_tree **out, git_tree *root,
			git_repository *repo, const char *target, int *fanout)
{
	int error;
	git_tree *subtree = NULL;

	*out = NULL;

	error = find_subtree_in_current_level(&subtree, repo, root, target, *fanout);
	if (error == GIT_EEXISTS)
		return git_tree_lookup(out, repo, git_tree_id(root));

	if (error < 0)
		return error;

	*fanout += 2;
	error = find_subtree_r(out, subtree, repo, target, fanout);
	git_tree_free(subtree);

	return error;
}