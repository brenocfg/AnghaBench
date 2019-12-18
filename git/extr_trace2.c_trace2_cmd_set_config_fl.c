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
 int /*<<< orphan*/  tr2_cfg_set_fl (char const*,int,char const*,char const*) ; 
 int /*<<< orphan*/  trace2_enabled ; 

void trace2_cmd_set_config_fl(const char *file, int line, const char *key,
			      const char *value)
{
	if (!trace2_enabled)
		return;

	tr2_cfg_set_fl(file, line, key, value);
}