#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct cam_path {TYPE_4__* device; TYPE_3__* target; TYPE_2__* periph; TYPE_1__* bus; } ;
struct TYPE_8__ {scalar_t__ refcount; } ;
struct TYPE_7__ {scalar_t__ refcount; } ;
struct TYPE_6__ {scalar_t__ refcount; } ;
struct TYPE_5__ {scalar_t__ refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 

void
xpt_path_counts(struct cam_path *path, uint32_t *bus_ref,
    uint32_t *periph_ref, uint32_t *target_ref, uint32_t *device_ref)
{

	xpt_lock_buses();
	if (bus_ref) {
		if (path->bus)
			*bus_ref = path->bus->refcount;
		else
			*bus_ref = 0;
	}
	if (periph_ref) {
		if (path->periph)
			*periph_ref = path->periph->refcount;
		else
			*periph_ref = 0;
	}
	xpt_unlock_buses();
	if (target_ref) {
		if (path->target)
			*target_ref = path->target->refcount;
		else
			*target_ref = 0;
	}
	if (device_ref) {
		if (path->device)
			*device_ref = path->device->refcount;
		else
			*device_ref = 0;
	}
}