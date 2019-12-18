#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  ignore; int /*<<< orphan*/  ignore_default; void* name; int /*<<< orphan*/  fetch_recurse; int /*<<< orphan*/  fetch_recurse_default; int /*<<< orphan*/  update; int /*<<< orphan*/  update_default; void* branch; void* url; void* path; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (void*) ; 
 int /*<<< orphan*/  GIT_SUBMODULE_STATUS_IN_CONFIG ; 
 int get_value (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,char*) ; 
 int /*<<< orphan*/  git__free (void*) ; 
 void* git__strdup (char const*) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_submodule_parse_ignore (int /*<<< orphan*/ *,char const*) ; 
 int git_submodule_parse_recurse (int /*<<< orphan*/ *,char const*) ; 
 int git_submodule_parse_update (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  looks_like_command_line_option (char const*) ; 
 scalar_t__ strcmp (void*,char const*) ; 

__attribute__((used)) static int submodule_read_config(git_submodule *sm, git_config *cfg)
{
	git_buf key = GIT_BUF_INIT;
	const char *value;
	int error, in_config = 0;

	/*
	 * TODO: Look up path in index and if it is present but not a GITLINK
	 * then this should be deleted (at least to match git's behavior)
	 */

	if ((error = get_value(&value, cfg, &key, sm->name, "path")) == 0) {
		in_config = 1;
		/* We would warn here if we had that API */
		if (!looks_like_command_line_option(value)) {
	/*
	 * TODO: if case insensitive filesystem, then the following strcmp
	 * should be strcasecmp
	 */
			if (strcmp(sm->name, value) != 0) {
				if (sm->path != sm->name)
					git__free(sm->path);
				sm->path = git__strdup(value);
				GIT_ERROR_CHECK_ALLOC(sm->path);
			}

		}
	} else if (error != GIT_ENOTFOUND) {
		goto cleanup;
	}

	if ((error = get_value(&value, cfg, &key, sm->name, "url")) == 0) {
		/* We would warn here if we had that API */
		if (!looks_like_command_line_option(value)) {
			in_config = 1;
			sm->url = git__strdup(value);
			GIT_ERROR_CHECK_ALLOC(sm->url);
		}
	} else if (error != GIT_ENOTFOUND) {
		goto cleanup;
	}

	if ((error = get_value(&value, cfg, &key, sm->name, "branch")) == 0) {
		in_config = 1;
		sm->branch = git__strdup(value);
		GIT_ERROR_CHECK_ALLOC(sm->branch);
	} else if (error != GIT_ENOTFOUND) {
		goto cleanup;
	}

	if ((error = get_value(&value, cfg, &key, sm->name, "update")) == 0) {
		in_config = 1;
		if ((error = git_submodule_parse_update(&sm->update, value)) < 0)
			goto cleanup;
		sm->update_default = sm->update;
	} else if (error != GIT_ENOTFOUND) {
		goto cleanup;
	}

	if ((error = get_value(&value, cfg, &key, sm->name, "fetchRecurseSubmodules")) == 0) {
		in_config = 1;
		if ((error = git_submodule_parse_recurse(&sm->fetch_recurse, value)) < 0)
			goto cleanup;
		sm->fetch_recurse_default = sm->fetch_recurse;
	} else if (error != GIT_ENOTFOUND) {
		goto cleanup;
	}

	if ((error = get_value(&value, cfg, &key, sm->name, "ignore")) == 0) {
		in_config = 1;
		if ((error = git_submodule_parse_ignore(&sm->ignore, value)) < 0)
			goto cleanup;
		sm->ignore_default = sm->ignore;
	} else if (error != GIT_ENOTFOUND) {
		goto cleanup;
	}

	if (in_config)
		sm->flags |= GIT_SUBMODULE_STATUS_IN_CONFIG;

	error = 0;

cleanup:
	git_buf_dispose(&key);
	return error;
}