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
struct lc_element {int dummy; } ;
struct drbd_interval {int sector; int size; } ;
struct drbd_device {int /*<<< orphan*/  al_wait; int /*<<< orphan*/  al_lock; int /*<<< orphan*/  act_log; } ;

/* Variables and functions */
 int AL_EXTENT_SHIFT ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,unsigned int) ; 
 struct lc_element* lc_find (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  lc_put (int /*<<< orphan*/ ,struct lc_element*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void drbd_al_complete_io(struct drbd_device *device, struct drbd_interval *i)
{
	/* for bios crossing activity log extent boundaries,
	 * we may need to activate two extents in one go */
	unsigned first = i->sector >> (AL_EXTENT_SHIFT-9);
	unsigned last = i->size == 0 ? first : (i->sector + (i->size >> 9) - 1) >> (AL_EXTENT_SHIFT-9);
	unsigned enr;
	struct lc_element *extent;
	unsigned long flags;

	D_ASSERT(device, first <= last);
	spin_lock_irqsave(&device->al_lock, flags);

	for (enr = first; enr <= last; enr++) {
		extent = lc_find(device->act_log, enr);
		if (!extent) {
			drbd_err(device, "al_complete_io() called on inactive extent %u\n", enr);
			continue;
		}
		lc_put(device->act_log, extent);
	}
	spin_unlock_irqrestore(&device->al_lock, flags);
	wake_up(&device->al_wait);
}