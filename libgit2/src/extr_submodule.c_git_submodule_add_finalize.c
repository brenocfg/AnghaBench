#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MODULES_FILE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int git_index_add_bypath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_submodule_add_to_index (TYPE_1__*,int) ; 

int git_submodule_add_finalize(git_submodule *sm)
{
	int error;
	git_index *index;

	assert(sm);

	if ((error = git_repository_index__weakptr(&index, sm->repo)) < 0 ||
		(error = git_index_add_bypath(index, GIT_MODULES_FILE)) < 0)
		return error;

	return git_submodule_add_to_index(sm, true);
}