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
typedef  size_t usb_test_quirk_p ;
typedef  size_t uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usb_attach_arg {int /*<<< orphan*/  info; TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__* autoQuirk; } ;

/* Variables and functions */
 scalar_t__ UQ_NONE ; 
 size_t USB_MAX_AUTO_QUIRK ; 

uint8_t
usb_test_quirk(const struct usb_attach_arg *uaa, uint16_t quirk)
{
	uint8_t found;
	uint8_t x;

	if (quirk == UQ_NONE)
		return (0);

	/* search the automatic per device quirks first */

	for (x = 0; x != USB_MAX_AUTO_QUIRK; x++) {
		if (uaa->device->autoQuirk[x] == quirk)
			return (1);
	}

	/* search global quirk table, if any */

	found = (usb_test_quirk_p) (&uaa->info, quirk);

	return (found);
}