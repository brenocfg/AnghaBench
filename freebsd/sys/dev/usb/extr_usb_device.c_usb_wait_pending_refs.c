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
struct usb_device {scalar_t__ refcount; int /*<<< orphan*/  ref_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 scalar_t__ USB_DEV_REF_MAX ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ref_lock ; 

__attribute__((used)) static void
usb_wait_pending_refs(struct usb_device *udev)
{
#if USB_HAVE_UGEN
	DPRINTF("Refcount = %d\n", (int)udev->refcount); 

	mtx_lock(&usb_ref_lock);
	udev->refcount--;
	while (1) {
		/* wait for any pending references to go away */
		if (udev->refcount == 0) {
			/* prevent further refs being taken, if any */
			udev->refcount = USB_DEV_REF_MAX;
			break;
		}
		cv_wait(&udev->ref_cv, &usb_ref_lock);
	}
	mtx_unlock(&usb_ref_lock);
#endif
}