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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_ether {int /*<<< orphan*/  ue_eaddr; int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; } ;
typedef  size_t ssize_t ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  mac ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 size_t OF_getprop (int,char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_valid_mac_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 size_t nitems (char const**) ; 
 int usb_fdt_get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
usb_fdt_get_mac_addr(device_t dev, struct usb_ether* ue)
{
	phandle_t node;
	ssize_t i, proplen;
	uint8_t mac[sizeof(ue->ue_eaddr)];
	static const char *properties[] = {
	    "mac-address",
	    "local-mac-address"
	};

	if ((node = usb_fdt_get_node(ue->ue_dev, ue->ue_udev)) == -1)
		return (ENXIO);
	for (i = 0; i < nitems(properties); ++i) {
		proplen = OF_getprop(node, properties[i], mac, sizeof(mac));
		if (proplen == sizeof(mac) && is_valid_mac_addr(mac)) {
			memcpy(ue->ue_eaddr, mac, sizeof(ue->ue_eaddr));
			return (0);
		}
	}
	return (ENXIO);
}