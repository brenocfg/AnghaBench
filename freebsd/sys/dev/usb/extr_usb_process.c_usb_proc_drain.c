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
struct usb_process {int up_gone; int /*<<< orphan*/ * up_mtx; int /*<<< orphan*/  up_drain; scalar_t__ up_dsleep; int /*<<< orphan*/  up_cv; scalar_t__ up_ptr; scalar_t__ up_csleep; scalar_t__ up_msleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  USB_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_MTX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_MTX_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_THREAD_SUSPEND (scalar_t__) ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
usb_proc_drain(struct usb_process *up)
{
	/* check if not initialised */
	if (up->up_mtx == NULL)
		return;
	/* handle special case with Giant */
	if (up->up_mtx != &Giant)
		USB_MTX_ASSERT(up->up_mtx, MA_NOTOWNED);

	USB_MTX_LOCK(up->up_mtx);

	/* Set the gone flag */

	up->up_gone = 1;

	while (up->up_ptr) {

		/* Check if we need to wakeup the USB process */

		if (up->up_msleep || up->up_csleep) {
			up->up_msleep = 0;
			up->up_csleep = 0;
			cv_signal(&up->up_cv);
		}
#ifndef EARLY_AP_STARTUP
		/* Check if we are still cold booted */
		if (cold) {
			USB_THREAD_SUSPEND(up->up_ptr);
			printf("WARNING: A USB process has "
			    "been left suspended\n");
			break;
		}
#endif
		cv_wait(&up->up_cv, up->up_mtx);
	}
	/* Check if someone is waiting - should not happen */

	if (up->up_dsleep) {
		up->up_dsleep = 0;
		cv_broadcast(&up->up_drain);
		DPRINTF("WARNING: Someone is waiting "
		    "for USB process drain!\n");
	}
	USB_MTX_UNLOCK(up->up_mtx);
}