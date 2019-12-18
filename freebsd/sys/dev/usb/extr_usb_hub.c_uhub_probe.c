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
struct TYPE_2__ {scalar_t__ bConfigIndex; scalar_t__ bDeviceClass; } ;
struct usb_attach_arg {scalar_t__ usb_mode; TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ UDCLASS_HUB ; 
 scalar_t__ USB_MODE_HOST ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 

int
uhub_probe(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);

	if (uaa->usb_mode != USB_MODE_HOST)
		return (ENXIO);

	/*
	 * The subclass for USB HUBs is currently ignored because it
	 * is 0 for some and 1 for others.
	 */
	if (uaa->info.bConfigIndex == 0 &&
	    uaa->info.bDeviceClass == UDCLASS_HUB)
		return (BUS_PROBE_DEFAULT);

	return (ENXIO);
}