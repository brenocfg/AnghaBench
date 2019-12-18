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
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_MAX_FULL_SPEED_ISOC_FRAMES ; 
 int /*<<< orphan*/  USB_MAX_HIGH_SPEED_ISOC_FRAMES ; 
#define  USB_SPEED_FULL 129 
#define  USB_SPEED_LOW 128 
 int usbd_get_speed (struct usb_device*) ; 

__attribute__((used)) static uint16_t
usb_max_isoc_frames(struct usb_device *dev)
{
	;				/* indent fix */
	switch (usbd_get_speed(dev)) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
		return (USB_MAX_FULL_SPEED_ISOC_FRAMES);
	default:
		return (USB_MAX_HIGH_SPEED_ISOC_FRAMES);
	}
}