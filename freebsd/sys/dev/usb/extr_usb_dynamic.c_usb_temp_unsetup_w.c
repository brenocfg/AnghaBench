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
struct usb_device {int /*<<< orphan*/ * usb_template_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbd_free_config_desc (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usb_temp_unsetup_w(struct usb_device *udev)
{
	usbd_free_config_desc(udev, udev->usb_template_ptr);
	udev->usb_template_ptr = NULL;
}