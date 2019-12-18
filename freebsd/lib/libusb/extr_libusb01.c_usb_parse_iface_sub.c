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
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/ * currextra; scalar_t__ currep; struct libusb20_interface* currifc; } ;
struct TYPE_5__ {int /*<<< orphan*/  currep; int /*<<< orphan*/  currifc; } ;
struct usb_parse_state {scalar_t__ preparse; TYPE_3__ a; TYPE_2__ b; } ;
struct usb_interface_descriptor {scalar_t__ bNumEndpoints; int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  iInterface; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; int /*<<< orphan*/  bAlternateSetting; int /*<<< orphan*/  bInterfaceNumber; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct TYPE_4__ {int /*<<< orphan*/  iInterface; int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; int /*<<< orphan*/  bAlternateSetting; int /*<<< orphan*/  bInterfaceNumber; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct libusb20_interface {scalar_t__ num_endpoints; scalar_t__ endpoints; int /*<<< orphan*/  extra; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_parse_endpoint (struct usb_parse_state*) ; 
 int /*<<< orphan*/  usb_parse_extra (struct usb_parse_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usb_parse_iface_sub(struct usb_parse_state *ps)
{
	struct libusb20_interface *aifc;
	struct usb_interface_descriptor *bifc;
	uint8_t x;

	aifc = ps->a.currifc;
	bifc = ps->b.currifc++;

	if (ps->preparse == 0) {
		/* copy descriptor fields */
		bifc->bLength = aifc->desc.bLength;
		bifc->bDescriptorType = aifc->desc.bDescriptorType;
		bifc->bInterfaceNumber = aifc->desc.bInterfaceNumber;
		bifc->bAlternateSetting = aifc->desc.bAlternateSetting;
		bifc->bNumEndpoints = aifc->num_endpoints;
		bifc->bInterfaceClass = aifc->desc.bInterfaceClass;
		bifc->bInterfaceSubClass = aifc->desc.bInterfaceSubClass;
		bifc->bInterfaceProtocol = aifc->desc.bInterfaceProtocol;
		bifc->iInterface = aifc->desc.iInterface;
		bifc->endpoint = ps->b.currep;
	}
	for (x = 0; x != aifc->num_endpoints; x++) {
		ps->a.currep = aifc->endpoints + x;
		usb_parse_endpoint(ps);
	}

	ps->a.currextra = &aifc->extra;
	usb_parse_extra(ps, &bifc->extra, &bifc->extralen);
	return;
}