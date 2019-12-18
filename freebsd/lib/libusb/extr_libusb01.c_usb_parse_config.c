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
struct TYPE_6__ {int /*<<< orphan*/ * currextra; scalar_t__ currifc; struct libusb20_config* currcfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  currifcw; struct usb_config_descriptor* currcfg; } ;
struct usb_parse_state {scalar_t__ preparse; TYPE_3__ a; TYPE_2__ b; } ;
struct usb_config_descriptor {scalar_t__ bNumInterfaces; int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; int /*<<< orphan*/  interface; int /*<<< orphan*/  MaxPower; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  iConfiguration; int /*<<< orphan*/  bConfigurationValue; int /*<<< orphan*/  wTotalLength; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct TYPE_4__ {int /*<<< orphan*/  bMaxPower; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  iConfiguration; int /*<<< orphan*/  bConfigurationValue; int /*<<< orphan*/  wTotalLength; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct libusb20_config {scalar_t__ num_interface; scalar_t__ interface; int /*<<< orphan*/  extra; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_parse_extra (struct usb_parse_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_parse_iface (struct usb_parse_state*) ; 

__attribute__((used)) static void
usb_parse_config(struct usb_parse_state *ps)
{
	struct libusb20_config *acfg;
	struct usb_config_descriptor *bcfg;
	uint8_t x;

	acfg = ps->a.currcfg;
	bcfg = ps->b.currcfg;

	if (ps->preparse == 0) {
		/* initialise config wrapper */
		bcfg->bLength = acfg->desc.bLength;
		bcfg->bDescriptorType = acfg->desc.bDescriptorType;
		bcfg->wTotalLength = acfg->desc.wTotalLength;
		bcfg->bNumInterfaces = acfg->num_interface;
		bcfg->bConfigurationValue = acfg->desc.bConfigurationValue;
		bcfg->iConfiguration = acfg->desc.iConfiguration;
		bcfg->bmAttributes = acfg->desc.bmAttributes;
		bcfg->MaxPower = acfg->desc.bMaxPower;
		bcfg->interface = ps->b.currifcw;
	}
	for (x = 0; x != acfg->num_interface; x++) {
		ps->a.currifc = acfg->interface + x;
		usb_parse_iface(ps);
	}

	ps->a.currextra = &acfg->extra;
	usb_parse_extra(ps, &bcfg->extra, &bcfg->extralen);
	return;
}