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
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  git_config_set_multivar_in_file_gently (char const*,char const*,char const*,char const*,int) ; 

void git_config_set_multivar_in_file(const char *config_filename,
				     const char *key, const char *value,
				     const char *value_regex, int multi_replace)
{
	if (!git_config_set_multivar_in_file_gently(config_filename, key, value,
						    value_regex, multi_replace))
		return;
	if (value)
		die(_("could not set '%s' to '%s'"), key, value);
	else
		die(_("could not unset '%s'"), key);
}