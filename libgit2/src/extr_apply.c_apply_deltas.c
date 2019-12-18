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
typedef  int /*<<< orphan*/  git_strmap ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reader ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_apply_options ;

/* Variables and functions */
 int apply_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strmap_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_strmap_new (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int apply_deltas(
	git_repository *repo,
	git_reader *pre_reader,
	git_index *preimage,
	git_reader *post_reader,
	git_index *postimage,
	git_diff *diff,
	const git_apply_options *opts)
{
	git_strmap *removed_paths;
	size_t i;
	int error = 0;

	if (git_strmap_new(&removed_paths) < 0)
		return -1;

	for (i = 0; i < git_diff_num_deltas(diff); i++) {
		if ((error = apply_one(repo, pre_reader, preimage, post_reader, postimage, diff, removed_paths, i, opts)) < 0)
			goto done;
	}

done:
	git_strmap_free(removed_paths);
	return error;
}