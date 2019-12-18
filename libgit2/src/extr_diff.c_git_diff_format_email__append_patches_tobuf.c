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
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 
 int git_patch_to_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_diff_format_email__append_patches_tobuf(
	git_buf *out,
	git_diff *diff)
{
	size_t i, deltas;
	int error = 0;

	deltas = git_diff_num_deltas(diff);

	for (i = 0; i < deltas; ++i) {
		git_patch *patch = NULL;

		if ((error = git_patch_from_diff(&patch, diff, i)) >= 0)
			error = git_patch_to_buf(out, patch);

		git_patch_free(patch);

		if (error < 0)
			break;
	}

	return error;
}