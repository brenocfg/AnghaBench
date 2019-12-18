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
 int GIT_COLOR_AUTO ; 
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

int git_config_colorbool(const char *var, const char *value)
{
	if (value) {
		if (!strcasecmp(value, "never"))
			return 0;
		if (!strcasecmp(value, "always"))
			return 1;
		if (!strcasecmp(value, "auto"))
			return GIT_COLOR_AUTO;
	}

	if (!var)
		return -1;

	/* Missing or explicit false to turn off colorization */
	if (!git_config_bool(var, value))
		return 0;

	/* any normal truth value defaults to 'auto' */
	return GIT_COLOR_AUTO;
}