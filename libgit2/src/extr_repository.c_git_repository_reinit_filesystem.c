#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  is_bare; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository__configmap_lookup_cache_clear (TYPE_1__*) ; 
 char* git_repository_path (TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_workdir (TYPE_1__*) ; 
 int /*<<< orphan*/  git_submodule_foreach (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int repo_init_fs_configs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 
 int repo_local_config (int /*<<< orphan*/ **,TYPE_2__*,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  repo_reinit_submodule_fs ; 

int git_repository_reinit_filesystem(git_repository *repo, int recurse)
{
	int error = 0;
	git_buf path = GIT_BUF_INIT;
	git_config *config = NULL;
	const char *repo_dir = git_repository_path(repo);

	if (!(error = repo_local_config(&config, &path, repo, repo_dir)))
		error = repo_init_fs_configs(
			config, path.ptr, repo_dir, git_repository_workdir(repo), true);

	git_config_free(config);
	git_buf_dispose(&path);

	git_repository__configmap_lookup_cache_clear(repo);

	if (!repo->is_bare && recurse)
		(void)git_submodule_foreach(repo, repo_reinit_submodule_fs, NULL);

	return error;
}