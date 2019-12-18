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
struct usb_temp_device_desc {int dummy; } ;
struct usb_device {TYPE_1__* usb_template_ptr; } ;
struct TYPE_2__ {struct usb_temp_device_desc const* tdd; } ;

/* Variables and functions */

__attribute__((used)) static const struct usb_temp_device_desc *
usb_temp_get_tdd(struct usb_device *udev)
{
	if (udev->usb_template_ptr == NULL) {
		return (NULL);
	}
	return (udev->usb_template_ptr->tdd);
}