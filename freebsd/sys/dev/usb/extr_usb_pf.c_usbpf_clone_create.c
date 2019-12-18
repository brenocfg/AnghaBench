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
struct usb_bus {int /*<<< orphan*/  parent; struct ifnet* ifp; } ;
struct ifnet {int if_dunit; int /*<<< orphan*/  if_flags; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_dname; struct usb_bus* if_softc; int /*<<< orphan*/  if_xname; } ;
struct if_clone {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_USB ; 
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  IFT_USB ; 
 int /*<<< orphan*/  USBPF_HDR_LEN ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int ifc_alloc_unit (struct if_clone*,int*) ; 
 int /*<<< orphan*/  ifc_free_unit (struct if_clone*,int) ; 
 int ifc_name2unit (char*,int*) ; 
 int /*<<< orphan*/  rt_ifmsg (struct ifnet*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct usb_bus* usbpf_ifname2ubus (char*) ; 
 int /*<<< orphan*/  usbpf_ioctl ; 
 int /*<<< orphan*/  usbusname ; 

__attribute__((used)) static int
usbpf_clone_create(struct if_clone *ifc, char *name, size_t len, caddr_t params)
{
	int error;
	int unit;
	struct ifnet *ifp;
	struct usb_bus *ubus;

	error = ifc_name2unit(name, &unit);
	if (error)
		return (error);
 	if (unit < 0)
		return (EINVAL);

	ubus = usbpf_ifname2ubus(name);
	if (ubus == NULL)
		return (1);
	if (ubus->ifp != NULL)
		return (1);

	error = ifc_alloc_unit(ifc, &unit);
	if (error) {
		device_printf(ubus->parent, "usbpf: Could not allocate "
		    "instance\n");
		return (error);
	}
	ifp = ubus->ifp = if_alloc(IFT_USB);
	if (ifp == NULL) {
		ifc_free_unit(ifc, unit);
		device_printf(ubus->parent, "usbpf: Could not allocate "
		    "instance\n");
		return (ENOSPC);
	}
	strlcpy(ifp->if_xname, name, sizeof(ifp->if_xname));
	ifp->if_softc = ubus;
	ifp->if_dname = usbusname;
	ifp->if_dunit = unit;
	ifp->if_ioctl = usbpf_ioctl;
	if_attach(ifp);
	ifp->if_flags |= IFF_UP;
	rt_ifmsg(ifp);
	/*
	 * XXX According to the specification of DLT_USB, it indicates
	 * packets beginning with USB setup header. But not sure all
	 * packets would be.
	 */
	bpfattach(ifp, DLT_USB, USBPF_HDR_LEN);

	return (0);
}