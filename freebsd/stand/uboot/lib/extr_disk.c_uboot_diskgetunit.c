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
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 TYPE_1__* stor_info ; 
 int stor_info_no ; 

int
uboot_diskgetunit(int type, int type_unit)
{
	int local_type_unit;
	int i;

	local_type_unit = 0;
	for (i = 0; i < stor_info_no; i++) {
		if ((stor_info[i].type & type) == type) {
			if (local_type_unit == type_unit) {
				return (i);
			}
			local_type_unit++;
		}
	}

	return (-1);
}