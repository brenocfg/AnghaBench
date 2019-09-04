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
 int /*<<< orphan*/  assert (int) ; 
 int diff_load_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int git_diff_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int git_diff_tree_to_workdir_with_index(
	git_diff **out,
	git_repository *repo,
	git_tree *tree,
	const git_diff_options *opts)
{
	git_diff *d1 = NULL, *d2 = NULL;
	git_index *index = NULL;
	int error = 0;

	assert(out && repo);

	*out = NULL;

	if ((error = diff_load_index(&index, repo)) < 0)
		return error;

	if (!(error = git_diff_tree_to_index(&d1, repo, tree, index, opts)) &&
		!(error = git_diff_index_to_workdir(&d2, repo, index, opts)))
		error = git_diff_merge(d1, d2);

	git_diff_free(d2);

	if (error) {
		git_diff_free(d1);
		d1 = NULL;
	}

	*out = d1;
	return error;
}