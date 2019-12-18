#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* chassis; } ;
typedef  TYPE_1__ ibnd_fabric_t ;
struct TYPE_6__ {unsigned char chassisnum; struct TYPE_6__* next; } ;
typedef  TYPE_2__ ibnd_chassis_t ;

/* Variables and functions */

__attribute__((used)) static ibnd_chassis_t *find_chassisnum(ibnd_fabric_t * fabric,
				       unsigned char chassisnum)
{
	ibnd_chassis_t *current;

	for (current = fabric->chassis; current; current = current->next)
		if (current->chassisnum == chassisnum)
			return current;

	return NULL;
}