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
struct drbd_interval {scalar_t__ waiting; } ;
struct drbd_peer_request {struct drbd_interval i; } ;
struct drbd_device {int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  write_requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_clear_interval (struct drbd_interval*) ; 
 int /*<<< orphan*/  drbd_remove_interval (int /*<<< orphan*/ *,struct drbd_interval*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbd_remove_epoch_entry_interval(struct drbd_device *device,
					     struct drbd_peer_request *peer_req)
{
	struct drbd_interval *i = &peer_req->i;

	drbd_remove_interval(&device->write_requests, i);
	drbd_clear_interval(i);

	/* Wake up any processes waiting for this peer request to complete.  */
	if (i->waiting)
		wake_up(&device->misc_wait);
}