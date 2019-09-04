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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_5__ {char const* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_LOCAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_PROGRAMDATA ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_SYSTEM ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_XDG ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_REPOSITORY_ITEM_CONFIG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_config_add_file_ondisk (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_repository_item_path (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_config(
	git_config **out,
	git_repository *repo,
	const char *global_config_path,
	const char *xdg_config_path,
	const char *system_config_path,
	const char *programdata_path)
{
	int error;
	git_buf config_path = GIT_BUF_INIT;
	git_config *cfg = NULL;

	assert(out);

	if ((error = git_config_new(&cfg)) < 0)
		return error;

	if (repo) {
		if ((error = git_repository_item_path(&config_path, repo, GIT_REPOSITORY_ITEM_CONFIG)) == 0)
			error = git_config_add_file_ondisk(cfg, config_path.ptr, GIT_CONFIG_LEVEL_LOCAL, repo, 0);

		if (error && error != GIT_ENOTFOUND)
			goto on_error;

		git_buf_dispose(&config_path);
	}

	if (global_config_path != NULL &&
		(error = git_config_add_file_ondisk(
			cfg, global_config_path, GIT_CONFIG_LEVEL_GLOBAL, repo, 0)) < 0 &&
		error != GIT_ENOTFOUND)
		goto on_error;

	if (xdg_config_path != NULL &&
		(error = git_config_add_file_ondisk(
			cfg, xdg_config_path, GIT_CONFIG_LEVEL_XDG, repo, 0)) < 0 &&
		error != GIT_ENOTFOUND)
		goto on_error;

	if (system_config_path != NULL &&
		(error = git_config_add_file_ondisk(
			cfg, system_config_path, GIT_CONFIG_LEVEL_SYSTEM, repo, 0)) < 0 &&
		error != GIT_ENOTFOUND)
		goto on_error;

	if (programdata_path != NULL &&
		(error = git_config_add_file_ondisk(
			cfg, programdata_path, GIT_CONFIG_LEVEL_PROGRAMDATA, repo, 0)) < 0 &&
		error != GIT_ENOTFOUND)
		goto on_error;

	git_error_clear(); /* clear any lingering ENOTFOUND errors */

	*out = cfg;
	return 0;

on_error:
	git_buf_dispose(&config_path);
	git_config_free(cfg);
	*out = NULL;
	return error;
}