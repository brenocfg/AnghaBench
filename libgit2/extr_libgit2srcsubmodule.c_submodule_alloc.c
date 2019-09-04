#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * branch; int /*<<< orphan*/ * repo; int /*<<< orphan*/  fetch_recurse_default; int /*<<< orphan*/  fetch_recurse; int /*<<< orphan*/  update_default; int /*<<< orphan*/  update; int /*<<< orphan*/  ignore_default; int /*<<< orphan*/  ignore; int /*<<< orphan*/  name; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_SUBMODULE ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_NONE ; 
 int /*<<< orphan*/  GIT_SUBMODULE_RECURSE_NO ; 
 int /*<<< orphan*/  GIT_SUBMODULE_UPDATE_CHECKOUT ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git__strdup (char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int submodule_alloc(
	git_submodule **out, git_repository *repo, const char *name)
{
	size_t namelen;
	git_submodule *sm;

	if (!name || !(namelen = strlen(name))) {
		git_error_set(GIT_ERROR_SUBMODULE, "invalid submodule name");
		return -1;
	}

	sm = git__calloc(1, sizeof(git_submodule));
	GIT_ERROR_CHECK_ALLOC(sm);

	sm->name = sm->path = git__strdup(name);
	if (!sm->name) {
		git__free(sm);
		return -1;
	}

	GIT_REFCOUNT_INC(sm);
	sm->ignore = sm->ignore_default = GIT_SUBMODULE_IGNORE_NONE;
	sm->update = sm->update_default = GIT_SUBMODULE_UPDATE_CHECKOUT;
	sm->fetch_recurse = sm->fetch_recurse_default = GIT_SUBMODULE_RECURSE_NO;
	sm->repo   = repo;
	sm->branch = NULL;

	*out = sm;
	return 0;
}