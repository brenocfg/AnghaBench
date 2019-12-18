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
struct TYPE_2__ {scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; } ;
struct usb_attach_arg {scalar_t__ usb_mode; TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ UICLASS_MASS ; 
 scalar_t__ UIPROTO_MASS_BBB ; 
 scalar_t__ UISUBCLASS_SCSI ; 
 scalar_t__ USB_MODE_HOST ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
umass_probe(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);

	if (uaa->usb_mode != USB_MODE_HOST ||
	    uaa->info.bInterfaceClass != UICLASS_MASS ||
	    uaa->info.bInterfaceSubClass != UISUBCLASS_SCSI ||
	    uaa->info.bInterfaceProtocol != UIPROTO_MASS_BBB ||
	    device_get_unit(dev) != 0)
		return (ENXIO);
	return (0);
}