#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_submodule_ignore_t ;
struct TYPE_11__ {unsigned int flags; int /*<<< orphan*/  wd_oid; int /*<<< orphan*/  index_oid; int /*<<< orphan*/  head_oid; TYPE_1__* repo; int /*<<< orphan*/  ignore; } ;
typedef  TYPE_2__ git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_10__ {int /*<<< orphan*/ * submodule_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_ALL ; 
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_DIRTY ; 
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_UNSPECIFIED ; 
 unsigned int GIT_SUBMODULE_STATUS__CLEAR_INTERNAL (unsigned int) ; 
 int GIT_SUBMODULE_STATUS__HEAD_OID_VALID ; 
 int GIT_SUBMODULE_STATUS__INDEX_OID_VALID ; 
 unsigned int GIT_SUBMODULE_STATUS__IN_FLAGS ; 
 int GIT_SUBMODULE_STATUS__WD_OID_VALID ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_open (int /*<<< orphan*/ **,TYPE_2__*) ; 
 scalar_t__ git_submodule_open_bare (int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  submodule_copy_oid_maybe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  submodule_get_index_status (unsigned int*,TYPE_2__*) ; 
 int /*<<< orphan*/  submodule_get_wd_status (unsigned int*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ submodule_update_head (TYPE_2__*) ; 
 scalar_t__ submodule_update_index (TYPE_2__*) ; 

int git_submodule__status(
	unsigned int *out_status,
	git_oid *out_head_id,
	git_oid *out_index_id,
	git_oid *out_wd_id,
	git_submodule *sm,
	git_submodule_ignore_t ign)
{
	unsigned int status;
	git_repository *smrepo = NULL;

	if (ign == GIT_SUBMODULE_IGNORE_UNSPECIFIED)
		ign = sm->ignore;

	/* only return location info if ignore == all */
	if (ign == GIT_SUBMODULE_IGNORE_ALL) {
		*out_status = (sm->flags & GIT_SUBMODULE_STATUS__IN_FLAGS);
		return 0;
	}

	/* If the user has requested caching submodule state, performing these
	 * expensive operations (especially `submodule_update_head`, which is
	 * bottlenecked on `git_repository_head_tree`) eliminates much of the
	 * advantage.  We will, therefore, interpret the request for caching to
	 * apply here to and skip them.
	 */

	if (sm->repo->submodule_cache == NULL) {
		/* refresh the index OID */
		if (submodule_update_index(sm) < 0)
			return -1;

		/* refresh the HEAD OID */
		if (submodule_update_head(sm) < 0)
			return -1;
	}

	/* for ignore == dirty, don't scan the working directory */
	if (ign == GIT_SUBMODULE_IGNORE_DIRTY) {
		/* git_submodule_open_bare will load WD OID data */
		if (git_submodule_open_bare(&smrepo, sm) < 0)
			git_error_clear();
		else
			git_repository_free(smrepo);
		smrepo = NULL;
	} else if (git_submodule_open(&smrepo, sm) < 0) {
		git_error_clear();
		smrepo = NULL;
	}

	status = GIT_SUBMODULE_STATUS__CLEAR_INTERNAL(sm->flags);

	submodule_get_index_status(&status, sm);
	submodule_get_wd_status(&status, sm, smrepo, ign);

	git_repository_free(smrepo);

	*out_status = status;

	submodule_copy_oid_maybe(out_head_id, &sm->head_oid,
		(sm->flags & GIT_SUBMODULE_STATUS__HEAD_OID_VALID) != 0);
	submodule_copy_oid_maybe(out_index_id, &sm->index_oid,
		(sm->flags & GIT_SUBMODULE_STATUS__INDEX_OID_VALID) != 0);
	submodule_copy_oid_maybe(out_wd_id, &sm->wd_oid,
		(sm->flags & GIT_SUBMODULE_STATUS__WD_OID_VALID) != 0);

	return 0;
}