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
struct submodule_parallel_fetch {scalar_t__ command_line_option; int default_option; int /*<<< orphan*/  r; } ;
struct submodule {int fetch_recurse; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ RECURSE_SUBMODULES_DEFAULT ; 
 int RECURSE_SUBMODULES_NONE ; 
 int /*<<< orphan*/  free (char*) ; 
 int parse_fetch_recurse_submodules_arg (char*,char const*) ; 
 int /*<<< orphan*/  repo_config_get_string_const (int /*<<< orphan*/ ,char*,char const**) ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_fetch_recurse_config(const struct submodule *submodule,
				    struct submodule_parallel_fetch *spf)
{
	if (spf->command_line_option != RECURSE_SUBMODULES_DEFAULT)
		return spf->command_line_option;

	if (submodule) {
		char *key;
		const char *value;

		int fetch_recurse = submodule->fetch_recurse;
		key = xstrfmt("submodule.%s.fetchRecurseSubmodules", submodule->name);
		if (!repo_config_get_string_const(spf->r, key, &value)) {
			fetch_recurse = parse_fetch_recurse_submodules_arg(key, value);
		}
		free(key);

		if (fetch_recurse != RECURSE_SUBMODULES_NONE)
			/* local config overrules everything except commandline */
			return fetch_recurse;
	}

	return spf->default_option;
}