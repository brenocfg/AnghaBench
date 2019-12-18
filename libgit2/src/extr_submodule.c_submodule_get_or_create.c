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
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_strmap ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 TYPE_1__* git_strmap_get (int /*<<< orphan*/ *,char const*) ; 
 int git_strmap_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_submodule_free (TYPE_1__*) ; 
 int submodule_alloc (TYPE_1__**,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int submodule_get_or_create(git_submodule **out, git_repository *repo, git_strmap *map, const char *name)
{
	git_submodule *sm = NULL;
	int error;

	if ((sm = git_strmap_get(map, name)) != NULL)
		goto done;

	/* if the submodule doesn't exist yet in the map, create it */
	if ((error = submodule_alloc(&sm, repo, name)) < 0)
		return error;

	if ((error = git_strmap_set(map, sm->name, sm)) < 0) {
		git_submodule_free(sm);
		return error;
	}

done:
	GIT_REFCOUNT_INC(sm);
	*out = sm;
	return 0;
}