#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {struct libusb20_interface* currifc; } ;
struct TYPE_4__ {int /*<<< orphan*/  currifc; int /*<<< orphan*/  currifcw; } ;
struct usb_parse_state {scalar_t__ preparse; TYPE_1__ a; TYPE_2__ b; } ;
struct usb_interface {scalar_t__ num_altsetting; int /*<<< orphan*/  altsetting; } ;
struct libusb20_interface {scalar_t__ num_altsetting; scalar_t__ altsetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_parse_iface_sub (struct usb_parse_state*) ; 

__attribute__((used)) static void
usb_parse_iface(struct usb_parse_state *ps)
{
	struct libusb20_interface *aifc;
	struct usb_interface *bifc;
	uint8_t x;

	aifc = ps->a.currifc;
	bifc = ps->b.currifcw++;

	if (ps->preparse == 0) {
		/* initialise interface wrapper */
		bifc->altsetting = ps->b.currifc;
		bifc->num_altsetting = aifc->num_altsetting + 1;
	}
	usb_parse_iface_sub(ps);

	for (x = 0; x != aifc->num_altsetting; x++) {
		ps->a.currifc = aifc->altsetting + x;
		usb_parse_iface_sub(ps);
	}
	return;
}