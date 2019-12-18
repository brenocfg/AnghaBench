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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usbd_lookup_info {scalar_t__ idVendor; scalar_t__ bcdDevice; scalar_t__ idProduct; } ;
struct TYPE_2__ {scalar_t__ vid; scalar_t__ lo_rev; scalar_t__ hi_rev; scalar_t__ pid; scalar_t__* quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ UQ_MATCH_VENDOR_ONLY ; 
 scalar_t__ UQ_NONE ; 
 scalar_t__ USB_DEV_QUIRKS_MAX ; 
 int /*<<< orphan*/  USB_MTX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_MTX_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_SUB_QUIRKS_MAX ; 
 int /*<<< orphan*/  usb_quirk_mtx ; 
 TYPE_1__* usb_quirks ; 
 int /*<<< orphan*/  usb_quirkstr (scalar_t__) ; 

__attribute__((used)) static uint8_t
usb_test_quirk_by_info(const struct usbd_lookup_info *info, uint16_t quirk)
{
	uint16_t x;
	uint16_t y;

	if (quirk == UQ_NONE)
		goto done;

	USB_MTX_LOCK(&usb_quirk_mtx);

	for (x = 0; x != USB_DEV_QUIRKS_MAX; x++) {
		/* see if quirk information does not match */
		if ((usb_quirks[x].vid != info->idVendor) ||
		    (usb_quirks[x].lo_rev > info->bcdDevice) ||
		    (usb_quirks[x].hi_rev < info->bcdDevice)) {
			continue;
		}
		/* see if quirk only should match vendor ID */
		if (usb_quirks[x].pid != info->idProduct) {
			if (usb_quirks[x].pid != 0)
				continue;

			for (y = 0; y != USB_SUB_QUIRKS_MAX; y++) {
				if (usb_quirks[x].quirks[y] == UQ_MATCH_VENDOR_ONLY)
					break;
			}
			if (y == USB_SUB_QUIRKS_MAX)
				continue;
		}
		/* lookup quirk */
		for (y = 0; y != USB_SUB_QUIRKS_MAX; y++) {
			if (usb_quirks[x].quirks[y] == quirk) {
				USB_MTX_UNLOCK(&usb_quirk_mtx);
				DPRINTF("Found quirk '%s'.\n", usb_quirkstr(quirk));
				return (1);
			}
		}
	}
	USB_MTX_UNLOCK(&usb_quirk_mtx);
done:
	return (0);			/* no quirk match */
}