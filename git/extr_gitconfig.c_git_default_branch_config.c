#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  AUTOREBASE_ALWAYS ; 
 int /*<<< orphan*/  AUTOREBASE_LOCAL ; 
 int /*<<< orphan*/  AUTOREBASE_NEVER ; 
 int /*<<< orphan*/  AUTOREBASE_REMOTE ; 
 int /*<<< orphan*/  BRANCH_TRACK_ALWAYS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  autorebase ; 
 int config_error_nonbool (char const*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_branch_track ; 
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_default_branch_config(const char *var, const char *value)
{
	if (!strcmp(var, "branch.autosetupmerge")) {
		if (value && !strcasecmp(value, "always")) {
			git_branch_track = BRANCH_TRACK_ALWAYS;
			return 0;
		}
		git_branch_track = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "branch.autosetuprebase")) {
		if (!value)
			return config_error_nonbool(var);
		else if (!strcmp(value, "never"))
			autorebase = AUTOREBASE_NEVER;
		else if (!strcmp(value, "local"))
			autorebase = AUTOREBASE_LOCAL;
		else if (!strcmp(value, "remote"))
			autorebase = AUTOREBASE_REMOTE;
		else if (!strcmp(value, "always"))
			autorebase = AUTOREBASE_ALWAYS;
		else
			return error(_("malformed value for %s"), var);
		return 0;
	}

	/* Add other config variables here and to Documentation/config.txt. */
	return 0;
}