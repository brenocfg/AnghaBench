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
struct drbd_device {int /*<<< orphan*/  suspend_cnt; } ;
typedef  enum bm_flag { ____Placeholder_bm_flag } bm_flag ;
struct TYPE_6__ {TYPE_2__* connection; } ;
struct TYPE_4__ {scalar_t__ task; } ;
struct TYPE_5__ {TYPE_1__ worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  drbd_bm_lock (struct drbd_device*,char*,int) ; 
 int /*<<< orphan*/  drbd_bm_unlock (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_resume_io (struct drbd_device*) ; 
 TYPE_3__* first_peer_device (struct drbd_device*) ; 

int drbd_bitmap_io_from_worker(struct drbd_device *device,
		int (*io_fn)(struct drbd_device *),
		char *why, enum bm_flag flags)
{
	int rv;

	D_ASSERT(device, current == first_peer_device(device)->connection->worker.task);

	/* open coded non-blocking drbd_suspend_io(device); */
	atomic_inc(&device->suspend_cnt);

	drbd_bm_lock(device, why, flags);
	rv = io_fn(device);
	drbd_bm_unlock(device);

	drbd_resume_io(device);

	return rv;
}