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
struct usb_bus {int dummy; } ;
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 scalar_t__ devclass_get_device (int /*<<< orphan*/ *,int) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ *) ; 
 struct usb_bus* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/ * usb_devclass_ptr ; 
 int /*<<< orphan*/  usb_needs_explore (struct usb_bus*,int) ; 

void
usb_needs_explore_all(void)
{
	struct usb_bus *bus;
	devclass_t dc;
	device_t dev;
	int max;

	DPRINTFN(3, "\n");

	dc = usb_devclass_ptr;
	if (dc == NULL) {
		DPRINTFN(0, "no devclass\n");
		return;
	}
	/*
	 * Explore all USB buses in parallel.
	 */
	max = devclass_get_maxunit(dc);
	while (max >= 0) {
		dev = devclass_get_device(dc, max);
		if (dev) {
			bus = device_get_softc(dev);
			if (bus) {
				usb_needs_explore(bus, 1);
			}
		}
		max--;
	}
}