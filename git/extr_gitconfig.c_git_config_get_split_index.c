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
 int /*<<< orphan*/  git_config_get_maybe_bool (char*,int*) ; 

int git_config_get_split_index(void)
{
	int val;

	if (!git_config_get_maybe_bool("core.splitindex", &val))
		return val;

	return -1; /* default value */
}