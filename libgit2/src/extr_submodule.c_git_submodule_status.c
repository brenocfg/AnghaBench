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
typedef  int /*<<< orphan*/  git_submodule_ignore_t ;
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int git_submodule__status (unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

int git_submodule_status(unsigned int *status, git_repository *repo, const char *name, git_submodule_ignore_t ignore)
{
	git_submodule *sm;
	int error;

	assert(status && repo && name);

	if ((error = git_submodule_lookup(&sm, repo, name)) < 0)
		return error;

	error = git_submodule__status(status, NULL, NULL, NULL, sm, ignore);
	git_submodule_free(sm);

	return error;
}