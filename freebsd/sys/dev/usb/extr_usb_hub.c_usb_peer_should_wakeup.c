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
typedef  int uint8_t ;
struct TYPE_6__ {scalar_t__ usb_mode; } ;
struct TYPE_5__ {scalar_t__* type_refs; scalar_t__ write_refs; scalar_t__ read_refs; } ;
struct usb_device {scalar_t__ power_mode; scalar_t__ driver_added_refcount; scalar_t__ re_enumerate_wait; TYPE_3__ flags; TYPE_2__ pwr_save; TYPE_1__* bus; } ;
struct TYPE_4__ {scalar_t__ driver_added_refcount; } ;

/* Variables and functions */
 size_t UE_ISOCHRONOUS ; 
 scalar_t__ USB_MODE_HOST ; 
 scalar_t__ USB_POWER_MODE_ON ; 
 scalar_t__ USB_RE_ENUM_DONE ; 
 scalar_t__ usb_peer_can_wakeup (struct usb_device*) ; 

__attribute__((used)) static uint8_t
usb_peer_should_wakeup(struct usb_device *udev)
{
	return (((udev->power_mode == USB_POWER_MODE_ON) &&
	    (udev->flags.usb_mode == USB_MODE_HOST)) ||
	    (udev->driver_added_refcount != udev->bus->driver_added_refcount) ||
	    (udev->re_enumerate_wait != USB_RE_ENUM_DONE) ||
	    (udev->pwr_save.type_refs[UE_ISOCHRONOUS] != 0) ||
	    (udev->pwr_save.write_refs != 0) ||
	    ((udev->pwr_save.read_refs != 0) &&
	    (udev->flags.usb_mode == USB_MODE_HOST) &&
	    (usb_peer_can_wakeup(udev) == 0)));
}