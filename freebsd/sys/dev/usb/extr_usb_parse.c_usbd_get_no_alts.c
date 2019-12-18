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
typedef  scalar_t__ uint8_t ;
struct usb_interface_descriptor {scalar_t__ bInterfaceNumber; } ;
struct usb_descriptor {scalar_t__ bDescriptorType; int bLength; } ;
struct usb_config_descriptor {int dummy; } ;

/* Variables and functions */
 scalar_t__ UDESC_INTERFACE ; 
 struct usb_descriptor* usb_desc_foreach (struct usb_config_descriptor*,struct usb_descriptor*) ; 

uint8_t
usbd_get_no_alts(struct usb_config_descriptor *cd,
    struct usb_interface_descriptor *id)
{
	struct usb_descriptor *desc;
	uint8_t n;
	uint8_t ifaceno;

	/* Reset interface count */

	n = 0;

	/* Get the interface number */

	ifaceno = id->bInterfaceNumber;

	/* Iterate all the USB descriptors */

	desc = NULL;
	while ((desc = usb_desc_foreach(cd, desc))) {
		if ((desc->bDescriptorType == UDESC_INTERFACE) &&
		    (desc->bLength >= sizeof(*id))) {
			id = (struct usb_interface_descriptor *)desc;
			if (id->bInterfaceNumber == ifaceno) {
				n++;
				if (n == 0xFF)
					break;		/* crazy */
			}
		}
	}
	return (n);
}