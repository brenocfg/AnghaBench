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
struct usb_interface_descriptor {scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; } ;
struct usb_attach_arg {scalar_t__ usb_mode; int /*<<< orphan*/  iface; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 scalar_t__ UICLASS_MASS ; 
 scalar_t__ UIPROTO_MASS_BBB ; 
 scalar_t__ UISUBCLASS_SCSI ; 
 scalar_t__ USB_MODE_DEVICE ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ustorage_fs_probe(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct usb_interface_descriptor *id;

	if (uaa->usb_mode != USB_MODE_DEVICE) {
		return (ENXIO);
	}
	/* Check for a standards compliant device */
	id = usbd_get_interface_descriptor(uaa->iface);
	if ((id == NULL) ||
	    (id->bInterfaceClass != UICLASS_MASS) ||
	    (id->bInterfaceSubClass != UISUBCLASS_SCSI) ||
	    (id->bInterfaceProtocol != UIPROTO_MASS_BBB)) {
		return (ENXIO);
	}
	return (BUS_PROBE_GENERIC);
}