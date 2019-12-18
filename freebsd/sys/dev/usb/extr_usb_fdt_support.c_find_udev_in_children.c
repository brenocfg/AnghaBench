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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {scalar_t__ port_index; TYPE_1__ ddesc; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  port ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  compat ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_node_is_compatible (scalar_t__,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static phandle_t
find_udev_in_children(phandle_t parent, struct usb_device *udev)
{
	phandle_t child;
	ssize_t proplen;
	uint32_t port;
	char compat[16]; /* big enough for "usb1234,abcd" */

	/*
	 * USB device nodes in FDT have a compatible string of "usb" followed by
	 * the vendorId,productId rendered in hex.  The port number is encoded
	 * in the standard 'reg' property; it is one-based in the FDT data, but
	 * usb_device.port_index is zero-based.  To uniquely identify a device,
	 * both the compatible string and the port number must match.
	 */
	snprintf(compat, sizeof(compat), "usb%x,%x",
	    UGETW(udev->ddesc.idVendor), UGETW(udev->ddesc.idProduct));
	for (child = OF_child(parent); child != 0; child = OF_peer(child)) {
		if (!ofw_bus_node_is_compatible(child, compat))
			continue;
		proplen = OF_getencprop(child, "reg", &port, sizeof(port));
		if (proplen != sizeof(port))
			continue;
		if (port == (udev->port_index + 1))
			return (child);
	}
	return (-1);
}