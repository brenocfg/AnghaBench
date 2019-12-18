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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_device {scalar_t__ re_enumerate_wait; scalar_t__ curr_config_index; scalar_t__ next_config_index; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ERR_PENDING_REQUESTS ; 
 scalar_t__ USB_RE_ENUM_DONE ; 
 scalar_t__ USB_RE_ENUM_SET_CONFIG ; 
 int /*<<< orphan*/  usb_needs_explore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

usb_error_t
usbd_start_set_config(struct usb_device *udev, uint8_t index)
{
	if (udev->re_enumerate_wait == USB_RE_ENUM_DONE) {
		if (udev->curr_config_index == index) {
			/* no change needed */
			return (0);
		}
		udev->next_config_index = index;
		udev->re_enumerate_wait = USB_RE_ENUM_SET_CONFIG;
		usb_needs_explore(udev->bus, 0);
		return (0);
	} else if (udev->re_enumerate_wait == USB_RE_ENUM_SET_CONFIG) {
		if (udev->next_config_index == index) {
			/* no change needed */
			return (0);
		}
	}
	return (USB_ERR_PENDING_REQUESTS);
}