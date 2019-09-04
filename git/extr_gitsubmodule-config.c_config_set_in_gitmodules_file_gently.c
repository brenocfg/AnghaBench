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
 int /*<<< orphan*/  GITMODULES_FILE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int git_config_set_in_file_gently (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 

int config_set_in_gitmodules_file_gently(const char *key, const char *value)
{
	int ret;

	ret = git_config_set_in_file_gently(GITMODULES_FILE, key, value);
	if (ret < 0)
		/* Maybe the user already did that, don't error out here */
		warning(_("Could not update .gitmodules entry %s"), key);

	return ret;
}