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
typedef  scalar_t__ timestamp_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ approxidate (char const*) ; 
 int git_config_get_string_const (char const*,char const**) ; 
 int /*<<< orphan*/  git_die_config (char const*,int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int git_config_get_expiry(const char *key, const char **output)
{
	int ret = git_config_get_string_const(key, output);
	if (ret)
		return ret;
	if (strcmp(*output, "now")) {
		timestamp_t now = approxidate("now");
		if (approxidate(*output) >= now)
			git_die_config(key, _("Invalid %s: '%s'"), key, *output);
	}
	return ret;
}