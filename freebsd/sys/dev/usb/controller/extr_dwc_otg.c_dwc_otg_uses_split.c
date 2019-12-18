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
typedef  int uint8_t ;
struct usb_device {scalar_t__ speed; TYPE_1__* parent_hs_hub; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent_hub; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_HIGH ; 

__attribute__((used)) static uint8_t
dwc_otg_uses_split(struct usb_device *udev)
{
	/*
	 * When a LOW or FULL speed device is connected directly to
	 * the USB port we don't use split transactions:
	 */ 
	return (udev->speed != USB_SPEED_HIGH &&
	    udev->parent_hs_hub != NULL &&
	    udev->parent_hs_hub->parent_hub != NULL);
}