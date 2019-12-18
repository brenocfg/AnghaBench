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
struct drbd_device {int /*<<< orphan*/  al_lock; int /*<<< orphan*/  act_log; int /*<<< orphan*/  al_wait; } ;
struct bm_extent {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BME_PRIORITY ; 
 struct bm_extent* find_active_resync_extent (struct drbd_device*,unsigned int) ; 
 struct lc_element* lc_get (int /*<<< orphan*/ ,unsigned int) ; 
 struct lc_element* lc_try_get (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct lc_element *_al_get(struct drbd_device *device, unsigned int enr, bool nonblock)
{
	struct lc_element *al_ext;
	struct bm_extent *bm_ext;
	int wake;

	spin_lock_irq(&device->al_lock);
	bm_ext = find_active_resync_extent(device, enr);
	if (bm_ext) {
		wake = !test_and_set_bit(BME_PRIORITY, &bm_ext->flags);
		spin_unlock_irq(&device->al_lock);
		if (wake)
			wake_up(&device->al_wait);
		return NULL;
	}
	if (nonblock)
		al_ext = lc_try_get(device->act_log, enr);
	else
		al_ext = lc_get(device->act_log, enr);
	spin_unlock_irq(&device->al_lock);
	return al_ext;
}