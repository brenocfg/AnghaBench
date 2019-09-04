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
struct TYPE_5__ {int is_bare; int /*<<< orphan*/ * workdir; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int git_config__update_entry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int) ; 
 int git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,TYPE_1__*) ; 

int git_repository_set_bare(git_repository *repo)
{
	int error;
	git_config *config;

	assert(repo);

	if (repo->is_bare)
		return 0;

	if ((error = git_repository_config__weakptr(&config, repo)) < 0)
		return error;

	if ((error = git_config_set_bool(config, "core.bare", true)) < 0)
		return error;

	if ((error = git_config__update_entry(config, "core.worktree", NULL, true, true)) < 0)
		return error;

	git__free(repo->workdir);
	repo->workdir = NULL;
	repo->is_bare = 1;

	return 0;
}