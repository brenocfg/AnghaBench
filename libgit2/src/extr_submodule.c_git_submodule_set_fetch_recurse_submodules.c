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
typedef  int /*<<< orphan*/  git_submodule_recurse_t ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _sm_recurse_map ; 
 int /*<<< orphan*/  assert (int) ; 
 int write_mapped_var (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int git_submodule_set_fetch_recurse_submodules(git_repository *repo, const char *name, git_submodule_recurse_t recurse)
{
	assert(repo && name);

	return write_mapped_var(repo, name, _sm_recurse_map, ARRAY_SIZE(_sm_recurse_map), "fetchRecurseSubmodules", recurse);
}