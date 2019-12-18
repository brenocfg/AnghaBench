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
 scalar_t__ RECURSE_SUBMODULES_ON ; 
 scalar_t__ config_update_recurse_submodules ; 

int should_update_submodules(void)
{
	return config_update_recurse_submodules == RECURSE_SUBMODULES_ON;
}