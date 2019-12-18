#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ibnd_chassis_t ;
struct TYPE_4__ {TYPE_2__* current_chassis; TYPE_2__* last_chassis; TYPE_2__* first_chassis; } ;
typedef  TYPE_1__ chassis_scan_t ;
struct TYPE_5__ {struct TYPE_5__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_ERROR (char*) ; 
 TYPE_2__* calloc (int,int) ; 

__attribute__((used)) static int add_chassis(chassis_scan_t * chassis_scan)
{
	if (!(chassis_scan->current_chassis =
	      calloc(1, sizeof(ibnd_chassis_t)))) {
		IBND_ERROR("OOM: failed to allocate chassis object\n");
		return -1;
	}

	if (chassis_scan->first_chassis == NULL) {
		chassis_scan->first_chassis = chassis_scan->current_chassis;
		chassis_scan->last_chassis = chassis_scan->current_chassis;
	} else {
		chassis_scan->last_chassis->next =
		    chassis_scan->current_chassis;
		chassis_scan->last_chassis = chassis_scan->current_chassis;
	}
	return 0;
}