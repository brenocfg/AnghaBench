#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  delta; int /*<<< orphan*/  diff_opts; int /*<<< orphan*/  repo; } ;
struct TYPE_10__ {size_t delta_index; TYPE_1__ base; int /*<<< orphan*/  nfile; int /*<<< orphan*/  ofile; TYPE_3__* diff; } ;
typedef  TYPE_2__ git_patch_generated ;
struct TYPE_11__ {int /*<<< orphan*/  opts; int /*<<< orphan*/  deltas; int /*<<< orphan*/  repo; } ;
typedef  TYPE_3__ git_diff ;

/* Variables and functions */
 int git_diff_file_content__init_from_diff (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  patch_generated_init_common (TYPE_2__*) ; 
 int patch_generated_normalize_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int patch_generated_init(
	git_patch_generated *patch, git_diff *diff, size_t delta_index)
{
	int error = 0;

	memset(patch, 0, sizeof(*patch));

	patch->diff = diff;
	patch->base.repo = diff->repo;
	patch->base.delta = git_vector_get(&diff->deltas, delta_index);
	patch->delta_index = delta_index;

	if ((error = patch_generated_normalize_options(
			&patch->base.diff_opts, &diff->opts)) < 0 ||
		(error = git_diff_file_content__init_from_diff(
			&patch->ofile, diff, patch->base.delta, true)) < 0 ||
		(error = git_diff_file_content__init_from_diff(
			&patch->nfile, diff, patch->base.delta, false)) < 0)
		return error;

	patch_generated_init_common(patch);

	return 0;
}