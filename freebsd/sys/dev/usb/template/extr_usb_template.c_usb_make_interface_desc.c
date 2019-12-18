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
typedef  int uint16_t ;
struct usb_temp_setup {int size; scalar_t__ bNumEndpoints; scalar_t__ bAlternateSetting; scalar_t__ bInterfaceNumber; scalar_t__ buf; } ;
struct usb_temp_interface_desc {scalar_t__ isAltInterface; void** ppRawDesc; int /*<<< orphan*/  iInterface; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; struct usb_temp_endpoint_desc** ppEndpoints; } ;
struct usb_temp_endpoint_desc {int dummy; } ;
struct usb_interface_descriptor {int bLength; int /*<<< orphan*/  iInterface; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; scalar_t__ bNumEndpoints; scalar_t__ bAlternateSetting; scalar_t__ bInterfaceNumber; int /*<<< orphan*/  bDescriptorType; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDESC_INTERFACE ; 
 struct usb_interface_descriptor* USB_ADD_BYTES (scalar_t__,int) ; 
 int /*<<< orphan*/  usb_make_endpoint_desc (struct usb_temp_setup*,struct usb_temp_endpoint_desc const*) ; 
 int /*<<< orphan*/  usb_make_raw_desc (struct usb_temp_setup*,void const*) ; 

__attribute__((used)) static void
usb_make_interface_desc(struct usb_temp_setup *temp,
    const struct usb_temp_interface_desc *tid)
{
	struct usb_interface_descriptor *id;
	const struct usb_temp_endpoint_desc **ted;
	const void **rd;
	uint16_t old_size;

	/* Reserve memory */

	old_size = temp->size;
	temp->size += sizeof(*id);

	/* Update interface and alternate interface numbers */

	if (tid->isAltInterface == 0) {
		temp->bAlternateSetting = 0;
		temp->bInterfaceNumber++;
	} else {
		temp->bAlternateSetting++;
	}

	/* Scan all Raw Descriptors first */

	rd = tid->ppRawDesc;

	if (rd) {
		while (*rd) {
			usb_make_raw_desc(temp, *rd);
			rd++;
		}
	}
	/* Reset some counters */

	temp->bNumEndpoints = 0;

	/* Scan all Endpoint Descriptors second */

	ted = tid->ppEndpoints;
	if (ted) {
		while (*ted) {
			usb_make_endpoint_desc(temp, *ted);
			ted++;
		}
	}
	/*
	 * Fill out the real USB interface descriptor
	 * in case there is a buffer present:
	 */
	if (temp->buf) {
		id = USB_ADD_BYTES(temp->buf, old_size);
		id->bLength = sizeof(*id);
		id->bDescriptorType = UDESC_INTERFACE;
		id->bInterfaceNumber = temp->bInterfaceNumber;
		id->bAlternateSetting = temp->bAlternateSetting;
		id->bNumEndpoints = temp->bNumEndpoints;
		id->bInterfaceClass = tid->bInterfaceClass;
		id->bInterfaceSubClass = tid->bInterfaceSubClass;
		id->bInterfaceProtocol = tid->bInterfaceProtocol;
		id->iInterface = tid->iInterface;
	}
}