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
struct TYPE_2__ {scalar_t__ disk; } ;
struct drbd_device {TYPE_1__ state; int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  state_wait; } ;

/* Variables and functions */
 scalar_t__ D_FAILED ; 
 int ERR_INTR ; 
 int SS_IN_TRANSIENT_STATE ; 
 int SS_IS_DISKLESS ; 
 int SS_NOTHING_TO_DO ; 
 int /*<<< orphan*/  drbd_resume_io (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_suspend_io (struct drbd_device*) ; 
 int request_detach (struct drbd_device*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int drbd_request_detach_interruptible(struct drbd_device *device)
{
	int ret, rv;

	drbd_suspend_io(device); /* so no-one is stuck in drbd_al_begin_io */
	wait_event_interruptible(device->state_wait,
		(rv = request_detach(device)) != SS_IN_TRANSIENT_STATE);
	drbd_resume_io(device);

	ret = wait_event_interruptible(device->misc_wait,
			device->state.disk != D_FAILED);

	if (rv == SS_IS_DISKLESS)
		rv = SS_NOTHING_TO_DO;
	if (ret)
		rv = ERR_INTR;

	return rv;
}