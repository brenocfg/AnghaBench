#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  repo; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int GIT_SUBMODULE_STATUS_IN_WD ; 
 int GIT_SUBMODULE_STATUS__WD_FLAGS ; 
 int GIT_SUBMODULE_STATUS__WD_OID_VALID ; 
 int /*<<< orphan*/  GIT_UNUSED (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int git_submodule_name_is_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gitmodules_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int submodule_load_from_wd_lite (TYPE_1__*) ; 
 int submodule_read_config (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int submodule_update_head (TYPE_1__*) ; 
 int submodule_update_index (TYPE_1__*) ; 

int git_submodule_reload(git_submodule *sm, int force)
{
	int error = 0, isvalid;
	git_config *mods;

	GIT_UNUSED(force);

	assert(sm);

	isvalid = git_submodule_name_is_valid(sm->repo, sm->name, 0);
	if (isvalid <= 0) {
		/* This should come with a warning, but we've no API for that */
		return isvalid;
	}

	if (!git_repository_is_bare(sm->repo)) {
		/* refresh config data */
		if ((error = gitmodules_snapshot(&mods, sm->repo)) < 0 && error != GIT_ENOTFOUND)
			return error;
		if (mods != NULL) {
			error = submodule_read_config(sm, mods);
			git_config_free(mods);

			if (error < 0)
				return error;
		}

		/* refresh wd data */
		sm->flags &=
			~(GIT_SUBMODULE_STATUS_IN_WD |
			  GIT_SUBMODULE_STATUS__WD_OID_VALID |
			  GIT_SUBMODULE_STATUS__WD_FLAGS);

		error = submodule_load_from_wd_lite(sm);
	}

	if (error == 0 && (error = submodule_update_index(sm)) == 0)
		error = submodule_update_head(sm);

	return error;
}