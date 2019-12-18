#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ibnd_fabric_t ;
struct TYPE_3__ {int /*<<< orphan*/  chassisguid; } ;
typedef  TYPE_1__ ibnd_chassis_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_DEBUG (char*) ; 
 TYPE_1__* find_chassisnum (int /*<<< orphan*/ *,unsigned char) ; 

uint64_t ibnd_get_chassis_guid(ibnd_fabric_t * fabric, unsigned char chassisnum)
{
	ibnd_chassis_t *chassis;

	if (!fabric) {
		IBND_DEBUG("fabric parameter NULL\n");
		return 0;
	}

	chassis = find_chassisnum(fabric, chassisnum);
	if (chassis)
		return chassis->chassisguid;
	else
		return 0;
}