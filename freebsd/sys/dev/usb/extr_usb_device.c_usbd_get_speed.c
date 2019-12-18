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
struct usb_device {int speed; } ;
typedef  enum usb_dev_speed { ____Placeholder_usb_dev_speed } usb_dev_speed ;

/* Variables and functions */

enum usb_dev_speed
usbd_get_speed(struct usb_device *udev)
{
	return (udev->speed);
}