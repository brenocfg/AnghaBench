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
struct usb_device {int state; } ;
typedef  enum usb_dev_state { ____Placeholder_usb_dev_state } usb_dev_state ;

/* Variables and functions */
 int USB_STATE_DETACHED ; 

enum usb_dev_state
usb_get_device_state(struct usb_device *udev)
{
	if (udev == NULL)
		return (USB_STATE_DETACHED);
	return (udev->state);
}