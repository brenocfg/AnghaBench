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
struct TYPE_2__ {int bInterfaceClass; int bInterfaceSubClass; } ;
struct usb_attach_arg {scalar_t__ usb_mode; TYPE_1__ info; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ USB_MODE_HOST ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_get_manufacturer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ubser_probe(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);

	if (uaa->usb_mode != USB_MODE_HOST) {
		return (ENXIO);
	}
	/* check if this is a BWCT vendor specific ubser interface */
	if ((strcmp(usb_get_manufacturer(uaa->device), "BWCT") == 0) &&
	    (uaa->info.bInterfaceClass == 0xff) &&
	    (uaa->info.bInterfaceSubClass == 0x00))
		return (0);

	return (ENXIO);
}