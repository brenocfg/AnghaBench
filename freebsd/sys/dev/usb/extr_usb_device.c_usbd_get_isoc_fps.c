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
typedef  int uint32_t ;
struct usb_device {int speed; } ;

/* Variables and functions */
#define  USB_SPEED_FULL 129 
#define  USB_SPEED_LOW 128 

uint32_t
usbd_get_isoc_fps(struct usb_device *udev)
{
	;				/* indent fix */
	switch (udev->speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
		return (1000);
	default:
		return (8000);
	}
}