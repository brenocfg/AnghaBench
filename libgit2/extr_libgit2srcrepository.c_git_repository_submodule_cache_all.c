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
struct TYPE_5__ {int /*<<< orphan*/  submodule_cache; } ;
typedef  TYPE_1__ git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int git_strmap_new (int /*<<< orphan*/ *) ; 
 int git_submodule__map (TYPE_1__*,int /*<<< orphan*/ ) ; 

int git_repository_submodule_cache_all(git_repository *repo)
{
	int error;

	assert(repo);

	if ((error = git_strmap_new(&repo->submodule_cache)))
		return error;

	error = git_submodule__map(repo, repo->submodule_cache);
	return error;
}