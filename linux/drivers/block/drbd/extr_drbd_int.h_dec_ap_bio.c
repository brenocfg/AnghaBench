#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  w; } ;
struct drbd_device {int /*<<< orphan*/  misc_wait; TYPE_2__ bm_io_work; int /*<<< orphan*/  flags; int /*<<< orphan*/  ap_bio_cnt; } ;
struct TYPE_6__ {TYPE_1__* connection; } ;
struct TYPE_4__ {int /*<<< orphan*/  sender_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_IO ; 
 int /*<<< orphan*/  BITMAP_IO_QUEUED ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int drbd_get_max_buffers (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* first_peer_device (struct drbd_device*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dec_ap_bio(struct drbd_device *device)
{
	int mxb = drbd_get_max_buffers(device);
	int ap_bio = atomic_dec_return(&device->ap_bio_cnt);

	D_ASSERT(device, ap_bio >= 0);

	if (ap_bio == 0 && test_bit(BITMAP_IO, &device->flags)) {
		if (!test_and_set_bit(BITMAP_IO_QUEUED, &device->flags))
			drbd_queue_work(&first_peer_device(device)->
				connection->sender_work,
				&device->bm_io_work.w);
	}

	/* this currently does wake_up for every dec_ap_bio!
	 * maybe rather introduce some type of hysteresis?
	 * e.g. (ap_bio == mxb/2 || ap_bio == 0) ? */
	if (ap_bio < mxb)
		wake_up(&device->misc_wait);
}