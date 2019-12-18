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
struct cam_et {int /*<<< orphan*/  ed_entries; TYPE_1__* bus; } ;
struct cam_ed {scalar_t__ lun_id; int /*<<< orphan*/  refcount; } ;
typedef  scalar_t__ lun_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  eb_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 struct cam_ed* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct cam_ed* TAILQ_NEXT (struct cam_ed*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cam_ed *
xpt_find_device(struct cam_et *target, lun_id_t lun_id)
{
	struct cam_ed *device;

	mtx_assert(&target->bus->eb_mtx, MA_OWNED);
	for (device = TAILQ_FIRST(&target->ed_entries);
	     device != NULL;
	     device = TAILQ_NEXT(device, links)) {
		if (device->lun_id == lun_id) {
			device->refcount++;
			break;
		}
	}
	return (device);
}