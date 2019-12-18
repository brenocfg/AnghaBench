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
struct usb_descriptor {scalar_t__ bDescriptorType; } ;
struct usb_config_descriptor {int dummy; } ;

/* Variables and functions */
 struct usb_descriptor* usb_desc_foreach (struct usb_config_descriptor*,struct usb_descriptor*) ; 

uint8_t
usbd_get_no_descriptors(struct usb_config_descriptor *cd, uint8_t type)
{
	struct usb_descriptor *desc = NULL;
	uint8_t count = 0;

	while ((desc = usb_desc_foreach(cd, desc))) {
		if (desc->bDescriptorType == type) {
			count++;
			if (count == 0xFF)
				break;			/* crazy */
		}
	}
	return (count);
}