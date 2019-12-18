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
struct drbd_device {int /*<<< orphan*/  al_wait; int /*<<< orphan*/  al_lock; int /*<<< orphan*/  resync_wenr; scalar_t__ resync_locked; int /*<<< orphan*/  resync; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_FAILED ; 
 int /*<<< orphan*/  LC_FREE ; 
 scalar_t__ get_ldev_if_state (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lc_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void drbd_rs_cancel_all(struct drbd_device *device)
{
	spin_lock_irq(&device->al_lock);

	if (get_ldev_if_state(device, D_FAILED)) { /* Makes sure ->resync is there. */
		lc_reset(device->resync);
		put_ldev(device);
	}
	device->resync_locked = 0;
	device->resync_wenr = LC_FREE;
	spin_unlock_irq(&device->al_lock);
	wake_up(&device->al_wait);
}