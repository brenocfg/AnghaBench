#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_submodule ;
struct TYPE_3__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ checkout_data ;

/* Variables and functions */
 unsigned int GIT_SUBMODULE_STATUS_IN_CONFIG ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_location (unsigned int*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool submodule_is_config_only(
	checkout_data *data,
	const char *path)
{
	git_submodule *sm = NULL;
	unsigned int sm_loc = 0;
	bool rval = false;

	if (git_submodule_lookup(&sm, data->repo, path) < 0)
		return true;

	if (git_submodule_location(&sm_loc, sm) < 0 ||
		sm_loc == GIT_SUBMODULE_STATUS_IN_CONFIG)
		rval = true;

	git_submodule_free(sm);

	return rval;
}