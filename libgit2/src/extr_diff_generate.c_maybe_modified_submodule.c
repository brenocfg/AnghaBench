#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ git_submodule_ignore_t ;
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_10__ {scalar_t__ ignore_submodules; } ;
struct TYPE_11__ {int /*<<< orphan*/  repo; TYPE_1__ opts; } ;
struct TYPE_14__ {TYPE_2__ base; } ;
typedef  TYPE_5__ git_diff_generated ;
typedef  int /*<<< orphan*/  git_delta_t ;
struct TYPE_15__ {TYPE_4__* oitem; TYPE_3__* nitem; } ;
typedef  TYPE_6__ diff_in_progress ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 scalar_t__ DIFF_FLAG_IS_SET (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_DELTA_MODIFIED ; 
 int /*<<< orphan*/  GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_IGNORE_SUBMODULES ; 
 int GIT_EEXISTS ; 
 scalar_t__ GIT_SUBMODULE_IGNORE_ALL ; 
 unsigned int GIT_SUBMODULE_STATUS_IN_WD ; 
 int /*<<< orphan*/  GIT_SUBMODULE_STATUS_IS_WD_UNMODIFIED (unsigned int) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_submodule__status (unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_ignore (int /*<<< orphan*/ *) ; 
 int git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maybe_modified_submodule(
	git_delta_t *status,
	git_oid *found_oid,
	git_diff_generated *diff,
	diff_in_progress *info)
{
	int error = 0;
	git_submodule *sub;
	unsigned int sm_status = 0;
	git_submodule_ignore_t ign = diff->base.opts.ignore_submodules;

	*status = GIT_DELTA_UNMODIFIED;

	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_IGNORE_SUBMODULES) ||
		ign == GIT_SUBMODULE_IGNORE_ALL)
		return 0;

	if ((error = git_submodule_lookup(
			&sub, diff->base.repo, info->nitem->path)) < 0) {

		/* GIT_EEXISTS means dir with .git in it was found - ignore it */
		if (error == GIT_EEXISTS) {
			git_error_clear();
			error = 0;
		}
		return error;
	}

	if (ign <= 0 && git_submodule_ignore(sub) == GIT_SUBMODULE_IGNORE_ALL)
		/* ignore it */;
	else if ((error = git_submodule__status(
			&sm_status, NULL, NULL, found_oid, sub, ign)) < 0)
		/* return error below */;

	/* check IS_WD_UNMODIFIED because this case is only used
	 * when the new side of the diff is the working directory
	 */
	else if (!GIT_SUBMODULE_STATUS_IS_WD_UNMODIFIED(sm_status))
		*status = GIT_DELTA_MODIFIED;

	/* now that we have a HEAD OID, check if HEAD moved */
	else if ((sm_status & GIT_SUBMODULE_STATUS_IN_WD) != 0 &&
		!git_oid_equal(&info->oitem->id, found_oid))
		*status = GIT_DELTA_MODIFIED;

	git_submodule_free(sub);
	return error;
}