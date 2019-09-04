#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ status; } ;
struct TYPE_22__ {int contains_data; } ;
struct TYPE_21__ {int flags; } ;
struct TYPE_23__ {TYPE_7__ binary; TYPE_6__ diff_opts; TYPE_4__* delta; } ;
struct TYPE_20__ {int flags; int opts_flags; TYPE_3__* file; } ;
struct TYPE_17__ {int flags; TYPE_1__* file; } ;
struct TYPE_15__ {TYPE_8__ base; TYPE_5__ ofile; TYPE_2__ nfile; } ;
struct TYPE_24__ {TYPE_4__ delta; TYPE_10__ patch; } ;
typedef  TYPE_9__ patch_generated_with_delta ;
typedef  int /*<<< orphan*/  git_xdiff_output ;
typedef  int /*<<< orphan*/  git_patch_generated_output ;
typedef  TYPE_10__ git_patch_generated ;
struct TYPE_18__ {int /*<<< orphan*/  id; } ;
struct TYPE_16__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_ADDED ; 
 scalar_t__ GIT_DELTA_DELETED ; 
 scalar_t__ GIT_DELTA_MODIFIED ; 
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 scalar_t__ GIT_DELTA_UNTRACKED ; 
 int GIT_DIFF_FLAG__NO_DATA ; 
 int GIT_DIFF_INCLUDE_UNMODIFIED ; 
 int GIT_DIFF_SHOW_BINARY ; 
 scalar_t__ git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int patch_generated_create (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  patch_generated_init_common (TYPE_10__*) ; 
 int patch_generated_invoke_file_callback (TYPE_10__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int diff_single_generate(patch_generated_with_delta *pd, git_xdiff_output *xo)
{
	int error = 0;
	git_patch_generated *patch = &pd->patch;
	bool has_old = ((patch->ofile.flags & GIT_DIFF_FLAG__NO_DATA) == 0);
	bool has_new = ((patch->nfile.flags & GIT_DIFF_FLAG__NO_DATA) == 0);

	pd->delta.status = has_new ?
		(has_old ? GIT_DELTA_MODIFIED : GIT_DELTA_ADDED) :
		(has_old ? GIT_DELTA_DELETED : GIT_DELTA_UNTRACKED);

	if (git_oid_equal(&patch->nfile.file->id, &patch->ofile.file->id))
		pd->delta.status = GIT_DELTA_UNMODIFIED;

	patch->base.delta = &pd->delta;

	patch_generated_init_common(patch);

	if (pd->delta.status == GIT_DELTA_UNMODIFIED &&
		!(patch->ofile.opts_flags & GIT_DIFF_INCLUDE_UNMODIFIED)) {

		/* Even empty patches are flagged as binary, and even though
		 * there's no difference, we flag this as "containing data"
		 * (the data is known to be empty, as opposed to wholly unknown).
		 */
		if (patch->base.diff_opts.flags & GIT_DIFF_SHOW_BINARY)
			patch->base.binary.contains_data = 1;

		return error;
	}

	error = patch_generated_invoke_file_callback(patch, (git_patch_generated_output *)xo);

	if (!error)
		error = patch_generated_create(patch, (git_patch_generated_output *)xo);

	return error;
}