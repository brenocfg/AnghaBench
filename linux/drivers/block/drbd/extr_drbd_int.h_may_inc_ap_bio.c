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
struct drbd_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  ap_bio_cnt; int /*<<< orphan*/  suspend_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_IO ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int drbd_get_max_buffers (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_state_is_stable (struct drbd_device*) ; 
 scalar_t__ drbd_suspended (struct drbd_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool may_inc_ap_bio(struct drbd_device *device)
{
	int mxb = drbd_get_max_buffers(device);

	if (drbd_suspended(device))
		return false;
	if (atomic_read(&device->suspend_cnt))
		return false;

	/* to avoid potential deadlock or bitmap corruption,
	 * in various places, we only allow new application io
	 * to start during "stable" states. */

	/* no new io accepted when attaching or detaching the disk */
	if (!drbd_state_is_stable(device))
		return false;

	/* since some older kernels don't have atomic_add_unless,
	 * and we are within the spinlock anyways, we have this workaround.  */
	if (atomic_read(&device->ap_bio_cnt) > mxb)
		return false;
	if (test_bit(BITMAP_IO, &device->flags))
		return false;
	return true;
}