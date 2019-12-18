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
struct usb_bus {int /*<<< orphan*/ * ifp; } ;
struct ifnet {int if_dunit; struct usb_bus* if_softc; } ;
struct if_clone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifc_free_unit (struct if_clone*,int) ; 

__attribute__((used)) static int
usbpf_clone_destroy(struct if_clone *ifc, struct ifnet *ifp)
{
	struct usb_bus *ubus;
	int unit;

	ubus = ifp->if_softc;
	unit = ifp->if_dunit;

	/*
	 * Lock USB before clearing the "ifp" pointer, to avoid
	 * clearing the pointer in the middle of a TAP operation:
	 */
	USB_BUS_LOCK(ubus);
	ubus->ifp = NULL;
	USB_BUS_UNLOCK(ubus);
	bpfdetach(ifp);
	if_detach(ifp);
	if_free(ifp);
	ifc_free_unit(ifc, unit);
	
	return (0);
}