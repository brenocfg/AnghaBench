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
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_LOCAL ; 
 int /*<<< orphan*/  GIT_MODULES_FILE ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_backend_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_config_backend_from_file (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_backend_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ git_path_isfile (int /*<<< orphan*/ ) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static git_config_backend *open_gitmodules(
	git_repository *repo,
	int okay_to_create)
{
	const char *workdir = git_repository_workdir(repo);
	git_buf path = GIT_BUF_INIT;
	git_config_backend *mods = NULL;

	if (workdir != NULL) {
		if (git_buf_joinpath(&path, workdir, GIT_MODULES_FILE) != 0)
			return NULL;

		if (okay_to_create || git_path_isfile(path.ptr)) {
			/* git_config_backend_from_file should only fail if OOM */
			if (git_config_backend_from_file(&mods, path.ptr) < 0)
				mods = NULL;
			/* open should only fail here if the file is malformed */
			else if (git_config_backend_open(mods, GIT_CONFIG_LEVEL_LOCAL, repo) < 0) {
				git_config_backend_free(mods);
				mods = NULL;
			}
		}
	}

	git_buf_dispose(&path);

	return mods;
}