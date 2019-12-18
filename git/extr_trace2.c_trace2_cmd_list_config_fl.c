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
 int /*<<< orphan*/  tr2_cfg_list_config_fl (char const*,int) ; 
 int /*<<< orphan*/  trace2_enabled ; 

void trace2_cmd_list_config_fl(const char *file, int line)
{
	if (!trace2_enabled)
		return;

	tr2_cfg_list_config_fl(file, line);
}