#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct cam_ed {TYPE_1__* sim; scalar_t__ lun_id; TYPE_2__* target; } ;
struct TYPE_4__ {int /*<<< orphan*/  target_id; } ;
struct TYPE_3__ {char* sim_name; int unit_number; int bus_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
xpt_print_device(struct cam_ed *device)
{

	if (device == NULL)
		printf("(nopath): ");
	else {
		printf("(noperiph:%s%d:%d:%d:%jx): ", device->sim->sim_name,
		       device->sim->unit_number,
		       device->sim->bus_id,
		       device->target->target_id,
		       (uintmax_t)device->lun_id);
	}
}