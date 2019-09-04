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
 void* fetch_prune_config ; 
 void* fetch_prune_tags_config ; 
 void* git_config_bool (char const*,char const*) ; 
 int git_default_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  max_children ; 
 int parse_fetch_recurse_submodules_arg (char const*,char const*) ; 
 int /*<<< orphan*/  parse_submodule_fetchjobs (char const*,char const*) ; 
 int recurse_submodules ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

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

	if (!strcmp(k, "submodule.recurse")) {
		int r = git_config_bool(k, v) ?
			RECURSE_SUBMODULES_ON : RECURSE_SUBMODULES_OFF;
		recurse_submodules = r;
	}

	if (!strcmp(k, "submodule.fetchjobs")) {
		max_children = parse_submodule_fetchjobs(k, v);
		return 0;
	} else if (!strcmp(k, "fetch.recursesubmodules")) {
		recurse_submodules = parse_fetch_recurse_submodules_arg(k, v);
		return 0;
	}

	return git_default_config(k, v, cb);
}