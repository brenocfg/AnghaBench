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
struct TYPE_5__ {int /*<<< orphan*/ * _config; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_REFCOUNT_OWN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * git__compare_and_swap (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config__global_location (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_find_global (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_find_programdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_find_system (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_find_xdg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int load_config (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_unless_empty (int /*<<< orphan*/ *) ; 

int git_repository_config__weakptr(git_config **out, git_repository *repo)
{
	int error = 0;

	if (repo->_config == NULL) {
		git_buf global_buf = GIT_BUF_INIT;
		git_buf xdg_buf = GIT_BUF_INIT;
		git_buf system_buf = GIT_BUF_INIT;
		git_buf programdata_buf = GIT_BUF_INIT;
		git_config *config;

		git_config_find_global(&global_buf);
		git_config_find_xdg(&xdg_buf);
		git_config_find_system(&system_buf);
		git_config_find_programdata(&programdata_buf);

		/* If there is no global file, open a backend for it anyway */
		if (git_buf_len(&global_buf) == 0)
			git_config__global_location(&global_buf);

		error = load_config(
			&config, repo,
			path_unless_empty(&global_buf),
			path_unless_empty(&xdg_buf),
			path_unless_empty(&system_buf),
			path_unless_empty(&programdata_buf));
		if (!error) {
			GIT_REFCOUNT_OWN(config, repo);

			config = git__compare_and_swap(&repo->_config, NULL, config);
			if (config != NULL) {
				GIT_REFCOUNT_OWN(config, NULL);
				git_config_free(config);
			}
		}

		git_buf_dispose(&global_buf);
		git_buf_dispose(&xdg_buf);
		git_buf_dispose(&system_buf);
		git_buf_dispose(&programdata_buf);
	}

	*out = repo->_config;
	return error;
}