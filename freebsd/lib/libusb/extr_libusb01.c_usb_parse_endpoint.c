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
struct TYPE_6__ {int /*<<< orphan*/ * currextra; struct libusb20_endpoint* currep; } ;
struct TYPE_4__ {int /*<<< orphan*/  currep; } ;
struct usb_parse_state {scalar_t__ preparse; TYPE_3__ a; TYPE_1__ b; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; int /*<<< orphan*/  bSynchAddress; int /*<<< orphan*/  bRefresh; int /*<<< orphan*/  bInterval; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct TYPE_5__ {int /*<<< orphan*/  bSynchAddress; int /*<<< orphan*/  bRefresh; int /*<<< orphan*/  bInterval; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct libusb20_endpoint {int /*<<< orphan*/  extra; TYPE_2__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_parse_extra (struct usb_parse_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usb_parse_endpoint(struct usb_parse_state *ps)
{
	struct usb_endpoint_descriptor *bep;
	struct libusb20_endpoint *aep;

	aep = ps->a.currep;
	bep = ps->b.currep++;

	if (ps->preparse == 0) {
		/* copy descriptor fields */
		bep->bLength = aep->desc.bLength;
		bep->bDescriptorType = aep->desc.bDescriptorType;
		bep->bEndpointAddress = aep->desc.bEndpointAddress;
		bep->bmAttributes = aep->desc.bmAttributes;
		bep->wMaxPacketSize = aep->desc.wMaxPacketSize;
		bep->bInterval = aep->desc.bInterval;
		bep->bRefresh = aep->desc.bRefresh;
		bep->bSynchAddress = aep->desc.bSynchAddress;
	}
	ps->a.currextra = &aep->extra;
	usb_parse_extra(ps, &bep->extra, &bep->extralen);
	return;
}