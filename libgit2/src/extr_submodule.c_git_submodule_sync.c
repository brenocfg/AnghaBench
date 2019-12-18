#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; int /*<<< orphan*/  url; int /*<<< orphan*/  name; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_SUBMODULE ; 
 int GIT_SUBMODULE_STATUS_IN_WD ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_join3 (TYPE_2__*,char,char*,int /*<<< orphan*/ ,char*) ; 
 int git_buf_printf (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int git_buf_sets (TYPE_2__*,char*) ; 
 int git_config__update_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int git_submodule_open (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int lookup_head_remote_key (TYPE_2__*,int /*<<< orphan*/ *) ; 

int git_submodule_sync(git_submodule *sm)
{
	int error = 0;
	git_config *cfg = NULL;
	git_buf key = GIT_BUF_INIT;
	git_repository *smrepo = NULL;

	if (!sm->url) {
		git_error_set(GIT_ERROR_SUBMODULE,
			"no URL configured for submodule '%s'", sm->name);
		return -1;
	}

	/* copy URL over to config only if it already exists */

	if (!(error = git_repository_config__weakptr(&cfg, sm->repo)) &&
		!(error = git_buf_printf(&key, "submodule.%s.url", sm->name)))
		error = git_config__update_entry(cfg, key.ptr, sm->url, true, true);

	/* if submodule exists in the working directory, update remote url */

	if (!error &&
		(sm->flags & GIT_SUBMODULE_STATUS_IN_WD) != 0 &&
		!(error = git_submodule_open(&smrepo, sm)))
	{
		git_buf remote_name = GIT_BUF_INIT;

		if ((error = git_repository_config__weakptr(&cfg, smrepo)) < 0)
			/* return error from reading submodule config */;
		else if ((error = lookup_head_remote_key(&remote_name, smrepo)) < 0) {
			git_error_clear();
			error = git_buf_sets(&key, "remote.origin.url");
		} else {
			error = git_buf_join3(
				&key, '.', "remote", remote_name.ptr, "url");
			git_buf_dispose(&remote_name);
		}

		if (!error)
			error = git_config__update_entry(cfg, key.ptr, sm->url, true, false);

		git_repository_free(smrepo);
	}

	git_buf_dispose(&key);

	return error;
}