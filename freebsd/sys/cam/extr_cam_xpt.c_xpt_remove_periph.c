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
struct cam_periph {TYPE_1__* path; } ;
struct cam_ed {TYPE_3__* target; int /*<<< orphan*/  periphs; int /*<<< orphan*/  generation; } ;
struct TYPE_8__ {int /*<<< orphan*/  xpt_generation; } ;
struct TYPE_7__ {TYPE_2__* bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  eb_mtx; } ;
struct TYPE_5__ {struct cam_ed* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct cam_periph*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cam_periph ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  periph_links ; 
 TYPE_4__ xsoftc ; 

void
xpt_remove_periph(struct cam_periph *periph)
{
	struct cam_ed *device;

	device = periph->path->device;
	if (device != NULL) {
		mtx_lock(&device->target->bus->eb_mtx);
		device->generation++;
		SLIST_REMOVE(&device->periphs, periph, cam_periph, periph_links);
		mtx_unlock(&device->target->bus->eb_mtx);
		atomic_add_32(&xsoftc.xpt_generation, 1);
	}
}