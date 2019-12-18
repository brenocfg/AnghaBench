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
struct usb_bus {int /*<<< orphan*/ * cleanup_msg; int /*<<< orphan*/ * detach_msg; int /*<<< orphan*/  power_wdog; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_BUS_CONTROL_XFER_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_EXPLORE_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_GIANT_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_NON_GIANT_BULK_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_NON_GIANT_ISOC_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 struct usb_bus* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_msignal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_mwait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_root_mount_rel (struct usb_bus*) ; 
 int /*<<< orphan*/  usbpf_detach (struct usb_bus*) ; 

__attribute__((used)) static int
usb_detach(device_t dev)
{
	struct usb_bus *bus = device_get_softc(dev);

	DPRINTF("\n");

	if (bus == NULL) {
		/* was never setup properly */
		return (0);
	}
	/* Stop power watchdog */
	usb_callout_drain(&bus->power_wdog);

#if USB_HAVE_ROOT_MOUNT_HOLD
	/* Let the USB explore process detach all devices. */
	usb_root_mount_rel(bus);
#endif

	USB_BUS_LOCK(bus);

	/* Queue detach job */
	usb_proc_msignal(USB_BUS_EXPLORE_PROC(bus),
	    &bus->detach_msg[0], &bus->detach_msg[1]);

	/* Wait for detach to complete */
	usb_proc_mwait(USB_BUS_EXPLORE_PROC(bus),
	    &bus->detach_msg[0], &bus->detach_msg[1]);

#if USB_HAVE_UGEN
	/* Wait for cleanup to complete */
	usb_proc_mwait(USB_BUS_EXPLORE_PROC(bus),
	    &bus->cleanup_msg[0], &bus->cleanup_msg[1]);
#endif
	USB_BUS_UNLOCK(bus);

#if USB_HAVE_PER_BUS_PROCESS
	/* Get rid of USB callback processes */

	usb_proc_free(USB_BUS_GIANT_PROC(bus));
	usb_proc_free(USB_BUS_NON_GIANT_ISOC_PROC(bus));
	usb_proc_free(USB_BUS_NON_GIANT_BULK_PROC(bus));

	/* Get rid of USB explore process */

	usb_proc_free(USB_BUS_EXPLORE_PROC(bus));

	/* Get rid of control transfer process */

	usb_proc_free(USB_BUS_CONTROL_XFER_PROC(bus));
#endif

#if USB_HAVE_PF
	usbpf_detach(bus);
#endif
	return (0);
}