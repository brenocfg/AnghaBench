#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ bDescriptorType; int bInterfaceNumber; int bAlternateSetting; int bInterfaceClass; int bInterfaceSubClass; int bInterfaceProtocol; } ;
typedef  TYPE_1__ usb_interface_descriptor_t ;
typedef  int /*<<< orphan*/  usb_config_descriptor_t ;
struct usb_descriptor {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ UDESC_INTERFACE ; 
 struct usb_descriptor* usb_desc_foreach (int /*<<< orphan*/ *,struct usb_descriptor*) ; 

__attribute__((used)) static usb_interface_descriptor_t *
USBD_ParseConfigurationDescriptorEx(usb_config_descriptor_t *conf,
    void *start, int32_t intfnum, int32_t altset, int32_t intfclass,
    int32_t intfsubclass, int32_t intfproto)
{
	struct usb_descriptor *next = NULL;
	usb_interface_descriptor_t *desc;

	while ((next = usb_desc_foreach(conf, next)) != NULL) {
		desc = (usb_interface_descriptor_t *)next;
		if (desc->bDescriptorType != UDESC_INTERFACE)
			continue;
		if (!(intfnum == -1 || desc->bInterfaceNumber == intfnum))
			continue;
		if (!(altset == -1 || desc->bAlternateSetting == altset))
			continue;
		if (!(intfclass == -1 || desc->bInterfaceClass == intfclass))
			continue;
		if (!(intfsubclass == -1 ||
		    desc->bInterfaceSubClass == intfsubclass))
			continue;
		if (!(intfproto == -1 || desc->bInterfaceProtocol == intfproto))
			continue;
		return (desc);
	}

	return (NULL);
}