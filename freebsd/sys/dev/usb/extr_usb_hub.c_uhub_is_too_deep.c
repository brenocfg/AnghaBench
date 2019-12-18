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
typedef  int uint8_t ;
struct usb_device {int speed; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_HUB_MAX_DEPTH ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_SUPER 128 
 int /*<<< orphan*/  USB_SS_HUB_DEPTH_MAX ; 

__attribute__((used)) static uint8_t
uhub_is_too_deep(struct usb_device *udev)
{
	switch (udev->speed) {
	case USB_SPEED_FULL:
	case USB_SPEED_LOW:
	case USB_SPEED_HIGH:
		if (udev->depth > USB_HUB_MAX_DEPTH)
			return (1);
		break;
	case USB_SPEED_SUPER:
		if (udev->depth > USB_SS_HUB_DEPTH_MAX)
			return (1);
		break;
	default:
		break;
	}
	return (0);
}