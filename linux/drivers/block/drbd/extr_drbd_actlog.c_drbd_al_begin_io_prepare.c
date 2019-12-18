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
struct lc_element {unsigned int lc_number; } ;
struct drbd_interval {int sector; int size; } ;
struct drbd_device {int /*<<< orphan*/  al_wait; int /*<<< orphan*/  local_cnt; } ;

/* Variables and functions */
 int AL_EXTENT_SHIFT ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 struct lc_element* _al_get (struct drbd_device*,unsigned int,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool drbd_al_begin_io_prepare(struct drbd_device *device, struct drbd_interval *i)
{
	/* for bios crossing activity log extent boundaries,
	 * we may need to activate two extents in one go */
	unsigned first = i->sector >> (AL_EXTENT_SHIFT-9);
	unsigned last = i->size == 0 ? first : (i->sector + (i->size >> 9) - 1) >> (AL_EXTENT_SHIFT-9);
	unsigned enr;
	bool need_transaction = false;

	D_ASSERT(device, first <= last);
	D_ASSERT(device, atomic_read(&device->local_cnt) > 0);

	for (enr = first; enr <= last; enr++) {
		struct lc_element *al_ext;
		wait_event(device->al_wait,
				(al_ext = _al_get(device, enr, false)) != NULL);
		if (al_ext->lc_number != enr)
			need_transaction = true;
	}
	return need_transaction;
}