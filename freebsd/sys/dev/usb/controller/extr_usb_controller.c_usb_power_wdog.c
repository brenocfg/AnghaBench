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
struct usb_bus {int /*<<< orphan*/  power_wdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_EXPLORE_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (struct usb_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 int hz ; 
 int /*<<< orphan*/  usb_bus_power_update (struct usb_bus*) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),void*) ; 
 int /*<<< orphan*/  usb_proc_rewakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usb_power_wdog(void *arg)
{
	struct usb_bus *bus = arg;

	USB_BUS_LOCK_ASSERT(bus, MA_OWNED);

	usb_callout_reset(&bus->power_wdog,
	    4 * hz, usb_power_wdog, arg);

#ifdef DDB
	/*
	 * The following line of code is only here to recover from
	 * DDB:
	 */
	usb_proc_rewakeup(USB_BUS_EXPLORE_PROC(bus));	/* recover from DDB */
#endif

#if USB_HAVE_POWERD
	USB_BUS_UNLOCK(bus);

	usb_bus_power_update(bus);

	USB_BUS_LOCK(bus);
#endif
}