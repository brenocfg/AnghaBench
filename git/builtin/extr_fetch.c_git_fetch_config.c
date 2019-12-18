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
 int RECURSE_SUBMODULES_OFF ; 
 int RECURSE_SUBMODULES_ON ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ fetch_parallel_config ; 
 void* fetch_prune_config ; 
 void* fetch_prune_tags_config ; 
 void* fetch_show_forced_updates ; 
 void* git_config_bool (char const*,char const*) ; 
 scalar_t__ git_config_int (char const*,char const*) ; 
 int git_default_config (char const*,char const*,void*) ; 
 int parse_fetch_recurse_submodules_arg (char const*,char const*) ; 
 int /*<<< orphan*/  parse_submodule_fetchjobs (char const*,char const*) ; 
 int recurse_submodules ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  submodule_fetch_jobs_config ; 

__attribute__((used)) static int git_fetch_config(const char *k, const char *v, void *cb)
{
	if (!strcmp(k, "fetch.prune")) {
		fetch_prune_config = git_config_bool(k, v);
		return 0;
	}

	if (!strcmp(k, "fetch.prunetags")) {
		fetch_prune_tags_config = git_config_bool(k, v);
		return 0;
	}

	if (!strcmp(k, "fetch.showforcedupdates")) {
		fetch_show_forced_updates = git_config_bool(k, v);
		return 0;
	}

	if (!strcmp(k, "submodule.recurse")) {
		int r = git_config_bool(k, v) ?
			RECURSE_SUBMODULES_ON : RECURSE_SUBMODULES_OFF;
		recurse_submodules = r;
	}

	if (!strcmp(k, "submodule.fetchjobs")) {
		submodule_fetch_jobs_config = parse_submodule_fetchjobs(k, v);
		return 0;
	} else if (!strcmp(k, "fetch.recursesubmodules")) {
		recurse_submodules = parse_fetch_recurse_submodules_arg(k, v);
		return 0;
	}

	if (!strcmp(k, "fetch.parallel")) {
		fetch_parallel_config = git_config_int(k, v);
		if (fetch_parallel_config < 0)
			die(_("fetch.parallel cannot be negative"));
		return 0;
	}

	return git_default_config(k, v, cb);
}