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
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int git_config_int (char const*,char const*) ; 

int parse_submodule_fetchjobs(const char *var, const char *value)
{
	int fetchjobs = git_config_int(var, value);
	if (fetchjobs < 0)
		die(_("negative values not allowed for submodule.fetchjobs"));
	return fetchjobs;
}