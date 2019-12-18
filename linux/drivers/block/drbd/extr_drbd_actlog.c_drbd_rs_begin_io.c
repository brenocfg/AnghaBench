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
struct drbd_device {int /*<<< orphan*/  al_lock; int /*<<< orphan*/  al_wait; int /*<<< orphan*/  resync_locked; int /*<<< orphan*/  resync; } ;
struct bm_extent {scalar_t__ flags; int /*<<< orphan*/  lce; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int AL_EXT_PER_BM_SECT ; 
 int /*<<< orphan*/  BME_LOCKED ; 
 int /*<<< orphan*/  BME_PRIORITY ; 
 unsigned int BM_SECT_TO_EXT (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int HZ ; 
 struct bm_extent* _bme_get (struct drbd_device*,unsigned int) ; 
 int /*<<< orphan*/  _is_in_al (struct drbd_device*,unsigned int) ; 
 int drbd_rs_c_min_rate_throttle (struct drbd_device*) ; 
 scalar_t__ lc_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int drbd_rs_begin_io(struct drbd_device *device, sector_t sector)
{
	unsigned int enr = BM_SECT_TO_EXT(sector);
	struct bm_extent *bm_ext;
	int i, sig;
	bool sa;

retry:
	sig = wait_event_interruptible(device->al_wait,
			(bm_ext = _bme_get(device, enr)));
	if (sig)
		return -EINTR;

	if (test_bit(BME_LOCKED, &bm_ext->flags))
		return 0;

	/* step aside only while we are above c-min-rate; unless disabled. */
	sa = drbd_rs_c_min_rate_throttle(device);

	for (i = 0; i < AL_EXT_PER_BM_SECT; i++) {
		sig = wait_event_interruptible(device->al_wait,
					       !_is_in_al(device, enr * AL_EXT_PER_BM_SECT + i) ||
					       (sa && test_bit(BME_PRIORITY, &bm_ext->flags)));

		if (sig || (sa && test_bit(BME_PRIORITY, &bm_ext->flags))) {
			spin_lock_irq(&device->al_lock);
			if (lc_put(device->resync, &bm_ext->lce) == 0) {
				bm_ext->flags = 0; /* clears BME_NO_WRITES and eventually BME_PRIORITY */
				device->resync_locked--;
				wake_up(&device->al_wait);
			}
			spin_unlock_irq(&device->al_lock);
			if (sig)
				return -EINTR;
			if (schedule_timeout_interruptible(HZ/10))
				return -EINTR;
			goto retry;
		}
	}
	set_bit(BME_LOCKED, &bm_ext->flags);
	return 0;
}