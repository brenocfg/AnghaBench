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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 char** raid_levels ; 

char *pqisrc_raidlevel_to_string(uint8_t raid_level)
{
	DBG_FUNC("IN\n");
	if (raid_level < ARRAY_SIZE(raid_levels))
		return raid_levels[raid_level];
	DBG_FUNC("OUT\n");

	return " ";
}