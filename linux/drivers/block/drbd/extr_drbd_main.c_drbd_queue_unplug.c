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
struct TYPE_4__ {scalar_t__ pdsk; scalar_t__ conn; scalar_t__ role; } ;
struct drbd_device {int /*<<< orphan*/  unplug_work; int /*<<< orphan*/  flags; TYPE_1__ state; } ;
struct TYPE_6__ {TYPE_2__* connection; } ;
struct TYPE_5__ {int /*<<< orphan*/  sender_work; } ;

/* Variables and functions */
 scalar_t__ C_CONNECTED ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 scalar_t__ D_INCONSISTENT ; 
 scalar_t__ R_PRIMARY ; 
 int /*<<< orphan*/  UNPLUG_REMOTE ; 
 int /*<<< orphan*/  drbd_queue_work_if_unqueued (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* first_peer_device (struct drbd_device*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void drbd_queue_unplug(struct drbd_device *device)
{
	if (device->state.pdsk >= D_INCONSISTENT && device->state.conn >= C_CONNECTED) {
		D_ASSERT(device, device->state.role == R_PRIMARY);
		if (test_and_clear_bit(UNPLUG_REMOTE, &device->flags)) {
			drbd_queue_work_if_unqueued(
				&first_peer_device(device)->connection->sender_work,
				&device->unplug_work);
		}
	}
}