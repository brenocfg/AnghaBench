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
struct TYPE_2__ {int done; int /*<<< orphan*/  error; } ;
struct drbd_device {int /*<<< orphan*/  misc_wait; TYPE_1__ md_io; scalar_t__ ldev; } ;
struct bio {int /*<<< orphan*/  bi_status; struct drbd_device* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_md_put_buffer (struct drbd_device*) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void drbd_md_endio(struct bio *bio)
{
	struct drbd_device *device;

	device = bio->bi_private;
	device->md_io.error = blk_status_to_errno(bio->bi_status);

	/* special case: drbd_md_read() during drbd_adm_attach() */
	if (device->ldev)
		put_ldev(device);
	bio_put(bio);

	/* We grabbed an extra reference in _drbd_md_sync_page_io() to be able
	 * to timeout on the lower level device, and eventually detach from it.
	 * If this io completion runs after that timeout expired, this
	 * drbd_md_put_buffer() may allow us to finally try and re-attach.
	 * During normal operation, this only puts that extra reference
	 * down to 1 again.
	 * Make sure we first drop the reference, and only then signal
	 * completion, or we may (in drbd_al_read_log()) cycle so fast into the
	 * next drbd_md_sync_page_io(), that we trigger the
	 * ASSERT(atomic_read(&device->md_io_in_use) == 1) there.
	 */
	drbd_md_put_buffer(device);
	device->md_io.done = 1;
	wake_up(&device->misc_wait);
}