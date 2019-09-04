#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  data_cb; int /*<<< orphan*/  hunk_cb; int /*<<< orphan*/  binary_cb; } ;
typedef  TYPE_3__ git_patch_generated_output ;
struct TYPE_14__ {TYPE_1__* delta; int /*<<< orphan*/  diff_opts; } ;
struct TYPE_12__ {int opts_flags; int flags; TYPE_6__* file; } ;
struct TYPE_16__ {int flags; TYPE_2__ base; TYPE_11__ nfile; TYPE_11__ ofile; } ;
typedef  TYPE_4__ git_patch_generated ;
struct TYPE_17__ {int flags; scalar_t__ mode; int /*<<< orphan*/  id; } ;
struct TYPE_13__ {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_MODIFIED ; 
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 int GIT_DIFF_FLAG_VALID_ID ; 
 int GIT_DIFF_FLAG__NO_DATA ; 
 int GIT_DIFF_SKIP_BINARY_CHECK ; 
 scalar_t__ GIT_FILEMODE_COMMIT ; 
 int GIT_PATCH_GENERATED_DIFFABLE ; 
 int GIT_PATCH_GENERATED_LOADED ; 
 int git_diff_file_content__load (TYPE_11__*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ patch_generated_diffable (TYPE_4__*) ; 
 int /*<<< orphan*/  patch_generated_update_binary (TYPE_4__*) ; 
 scalar_t__ should_skip_binary (TYPE_4__*,TYPE_6__*) ; 

__attribute__((used)) static int patch_generated_load(git_patch_generated *patch, git_patch_generated_output *output)
{
	int error = 0;
	bool incomplete_data;

	if ((patch->flags & GIT_PATCH_GENERATED_LOADED) != 0)
		return 0;

	/* if no hunk and data callbacks and user doesn't care if data looks
	 * binary, then there is no need to actually load the data
	 */
	if ((patch->ofile.opts_flags & GIT_DIFF_SKIP_BINARY_CHECK) != 0 &&
		output && !output->binary_cb && !output->hunk_cb && !output->data_cb)
		return 0;

	incomplete_data =
		(((patch->ofile.flags & GIT_DIFF_FLAG__NO_DATA) != 0 ||
		  (patch->ofile.file->flags & GIT_DIFF_FLAG_VALID_ID) != 0) &&
		 ((patch->nfile.flags & GIT_DIFF_FLAG__NO_DATA) != 0 ||
		  (patch->nfile.file->flags & GIT_DIFF_FLAG_VALID_ID) != 0));

	if ((error = git_diff_file_content__load(
			&patch->ofile, &patch->base.diff_opts)) < 0 ||
		should_skip_binary(patch, patch->ofile.file))
		goto cleanup;
	if ((error = git_diff_file_content__load(
			&patch->nfile, &patch->base.diff_opts)) < 0 ||
		should_skip_binary(patch, patch->nfile.file))
		goto cleanup;

	/* if previously missing an oid, and now that we have it the two sides
	 * are the same (and not submodules), update MODIFIED -> UNMODIFIED
	 */
	if (incomplete_data &&
		patch->ofile.file->mode == patch->nfile.file->mode &&
		patch->ofile.file->mode != GIT_FILEMODE_COMMIT &&
		git_oid_equal(&patch->ofile.file->id, &patch->nfile.file->id) &&
		patch->base.delta->status == GIT_DELTA_MODIFIED) /* not RENAMED/COPIED! */
		patch->base.delta->status = GIT_DELTA_UNMODIFIED;

cleanup:
	patch_generated_update_binary(patch);

	if (!error) {
		if (patch_generated_diffable(patch))
			patch->flags |= GIT_PATCH_GENERATED_DIFFABLE;

		patch->flags |= GIT_PATCH_GENERATED_LOADED;
	}

	return error;
}