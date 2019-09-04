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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_config_get_maybe_bool (char*,int*) ; 
 int /*<<< orphan*/  git_config_get_value (char*,char const**) ; 
 scalar_t__ ignore_untracked_cache_config ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

int git_config_get_untracked_cache(void)
{
	int val = -1;
	const char *v;

	/* Hack for test programs like test-dump-untracked-cache */
	if (ignore_untracked_cache_config)
		return -1;

	if (!git_config_get_maybe_bool("core.untrackedcache", &val))
		return val;

	if (!git_config_get_value("core.untrackedcache", &v)) {
		if (!strcasecmp(v, "keep"))
			return -1;

		error(_("unknown core.untrackedCache value '%s'; "
			"using 'keep' default value"), v);
		return -1;
	}

	return -1; /* default value */
}