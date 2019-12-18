#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ update; int /*<<< orphan*/  name; int /*<<< orphan*/  url; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_9__ {char const* ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_SUBMODULE ; 
 scalar_t__ GIT_SUBMODULE_UPDATE_CHECKOUT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_printf (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int git_config__update_entry (int /*<<< orphan*/ *,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_submodule_resolve_url (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* git_submodule_update_to_str (scalar_t__) ; 

int git_submodule_init(git_submodule *sm, int overwrite)
{
	int error;
	const char *val;
	git_buf key = GIT_BUF_INIT, effective_submodule_url = GIT_BUF_INIT;
	git_config *cfg = NULL;

	if (!sm->url) {
		git_error_set(GIT_ERROR_SUBMODULE,
			"no URL configured for submodule '%s'", sm->name);
		return -1;
	}

	if ((error = git_repository_config(&cfg, sm->repo)) < 0)
		return error;

	/* write "submodule.NAME.url" */

	if ((error = git_submodule_resolve_url(&effective_submodule_url, sm->repo, sm->url)) < 0 ||
		(error = git_buf_printf(&key, "submodule.%s.url", sm->name)) < 0 ||
		(error = git_config__update_entry(
			cfg, key.ptr, effective_submodule_url.ptr, overwrite != 0, false)) < 0)
		goto cleanup;

	/* write "submodule.NAME.update" if not default */

	val = (sm->update == GIT_SUBMODULE_UPDATE_CHECKOUT) ?
		NULL : git_submodule_update_to_str(sm->update);

	if ((error = git_buf_printf(&key, "submodule.%s.update", sm->name)) < 0 ||
		(error = git_config__update_entry(
			cfg, key.ptr, val, overwrite != 0, false)) < 0)
		goto cleanup;

	/* success */

cleanup:
	git_config_free(cfg);
	git_buf_dispose(&key);
	git_buf_dispose(&effective_submodule_url);

	return error;
}