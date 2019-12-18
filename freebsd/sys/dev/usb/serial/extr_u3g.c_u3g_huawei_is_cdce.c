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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ USB_VENDOR_HUAWEI ; 

__attribute__((used)) static int
u3g_huawei_is_cdce(uint16_t idVendor, uint8_t bInterfaceSubClass,
    uint8_t bInterfaceProtocol)
{
	/*
	 * This function returns non-zero if the interface being
	 * probed is of type CDC ethernet, which the U3G driver should
	 * not attach to. See sys/dev/usb/net/if_cdce.c for matching
	 * entries.
	 */
	if (idVendor != USB_VENDOR_HUAWEI)
		goto done;

	switch (bInterfaceSubClass) {
	case 0x02:
		switch (bInterfaceProtocol) {
		case 0x16:
		case 0x46:
		case 0x76:
			return (1);
		default:
			break;
		}
		break;
	case 0x03:
		switch (bInterfaceProtocol) {
		case 0x16:
			return (1);
		default:
			break;
		}
		break;
	default:
		break;
	}
done:
	return (0);
}