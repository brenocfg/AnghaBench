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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_reinit_filesystem (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_submodule_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int repo_reinit_submodule_fs(git_submodule *sm, const char *n, void *p)
{
	git_repository *smrepo = NULL;
	GIT_UNUSED(n); GIT_UNUSED(p);

	if (git_submodule_open(&smrepo, sm) < 0 ||
		git_repository_reinit_filesystem(smrepo, true) < 0)
		git_error_clear();
	git_repository_free(smrepo);

	return 0;
}