#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cpufreq_policy {int dummy; } ;
struct TYPE_2__ {int driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_scale_voltage ; 
 size_t longhaul_index ; 
 int longhaul_setstate (struct cpufreq_policy*,unsigned int) ; 
 TYPE_1__* longhaul_table ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int longhaul_target(struct cpufreq_policy *policy,
			    unsigned int table_index)
{
	unsigned int i;
	unsigned int dir = 0;
	u8 vid, current_vid;
	int retval = 0;

	if (!can_scale_voltage)
		retval = longhaul_setstate(policy, table_index);
	else {
		/* On test system voltage transitions exceeding single
		 * step up or down were turning motherboard off. Both
		 * "ondemand" and "userspace" are unsafe. C7 is doing
		 * this in hardware, C3 is old and we need to do this
		 * in software. */
		i = longhaul_index;
		current_vid = (longhaul_table[longhaul_index].driver_data >> 8);
		current_vid &= 0x1f;
		if (table_index > longhaul_index)
			dir = 1;
		while (i != table_index) {
			vid = (longhaul_table[i].driver_data >> 8) & 0x1f;
			if (vid != current_vid) {
				retval = longhaul_setstate(policy, i);
				current_vid = vid;
				msleep(200);
			}
			if (dir)
				i++;
			else
				i--;
		}
		retval = longhaul_setstate(policy, table_index);
	}

	longhaul_index = table_index;
	return retval;
}