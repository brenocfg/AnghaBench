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
 int /*<<< orphan*/ * core_fsmonitor ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 scalar_t__ git_config_get_pathname (char*,int /*<<< orphan*/ **) ; 

int git_config_get_fsmonitor(void)
{
	if (git_config_get_pathname("core.fsmonitor", &core_fsmonitor))
		core_fsmonitor = getenv("GIT_TEST_FSMONITOR");

	if (core_fsmonitor && !*core_fsmonitor)
		core_fsmonitor = NULL;

	if (core_fsmonitor)
		return 1;

	return 0;
}