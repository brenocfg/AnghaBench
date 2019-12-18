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
typedef  int /*<<< orphan*/  usb_handle_req_t ;
struct TYPE_4__ {scalar_t__ usb_mode; } ;
struct usb_device {TYPE_3__* bus; int /*<<< orphan*/ * parent_hub; TYPE_1__ flags; } ;
struct TYPE_6__ {TYPE_2__* methods; } ;
struct TYPE_5__ {int /*<<< orphan*/ * roothub_exec; } ;

/* Variables and functions */
 scalar_t__ USB_MODE_DEVICE ; 
 int /*<<< orphan*/ * usb_temp_get_desc_p ; 

__attribute__((used)) static usb_handle_req_t *
usbd_get_hr_func(struct usb_device *udev)
{
	/* figure out if there is a Handle Request function */
	if (udev->flags.usb_mode == USB_MODE_DEVICE)
		return (usb_temp_get_desc_p);
	else if (udev->parent_hub == NULL)
		return (udev->bus->methods->roothub_exec);
	else
		return (NULL);
}