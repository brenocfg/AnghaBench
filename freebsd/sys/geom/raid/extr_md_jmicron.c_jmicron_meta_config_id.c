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
typedef  scalar_t__ uint32_t ;
struct jmicron_raid_conf {int* disks; } ;

/* Variables and functions */
 int JMICRON_MAX_DISKS ; 

__attribute__((used)) static uint32_t
jmicron_meta_config_id(struct jmicron_raid_conf *meta)
{
	int pos;
	uint32_t config_id;

	config_id = 0;
	for (pos = 0; pos < JMICRON_MAX_DISKS; pos++)
		config_id += meta->disks[pos] << pos;
	return (config_id);
}