#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int state; TYPE_2__* bus; } ;
typedef  enum usb_dev_state { ____Placeholder_usb_dev_state } usb_dev_state ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* device_state_change ) (struct usb_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int USB_STATE_MAX ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct usb_device*) ; 
 int /*<<< orphan*/  usb_ref_lock ; 
 int /*<<< orphan*/  usb_statestr (int) ; 

void
usb_set_device_state(struct usb_device *udev, enum usb_dev_state state)
{

	KASSERT(state < USB_STATE_MAX, ("invalid udev state"));

	DPRINTF("udev %p state %s -> %s\n", udev,
	    usb_statestr(udev->state), usb_statestr(state));

#if USB_HAVE_UGEN
	mtx_lock(&usb_ref_lock);
#endif
	udev->state = state;
#if USB_HAVE_UGEN
	mtx_unlock(&usb_ref_lock);
#endif
	if (udev->bus->methods->device_state_change != NULL)
		(udev->bus->methods->device_state_change) (udev);
}