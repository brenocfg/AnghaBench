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
struct usb_ether {int /*<<< orphan*/ * ue_methods; int /*<<< orphan*/ * ue_mtx; int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; struct ipheth_softc* ue_sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; } ;
struct ipheth_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_iface_no; struct usb_ether sc_ue; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IPHETH_ALT_INTFNUM ; 
 int /*<<< orphan*/  IPHETH_N_TRANSFER ; 
 int /*<<< orphan*/  MTX_DEF ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ipheth_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipheth_config ; 
 int /*<<< orphan*/  ipheth_detach (int /*<<< orphan*/ ) ; 
 int ipheth_get_mac_addr (struct ipheth_softc*) ; 
 int /*<<< orphan*/  ipheth_ue_methods ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uether_ifattach (struct usb_ether*) ; 
 int usbd_set_alt_interface_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipheth_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipheth_attach(device_t dev)
{
	struct ipheth_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	int error;

	sc->sc_iface_no = uaa->info.bIfaceIndex;

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	error = usbd_set_alt_interface_index(uaa->device,
	    uaa->info.bIfaceIndex, IPHETH_ALT_INTFNUM);
	if (error) {
		device_printf(dev, "Cannot set alternate setting\n");
		goto detach;
	}
	error = usbd_transfer_setup(uaa->device, &sc->sc_iface_no,
	    sc->sc_xfer, ipheth_config, IPHETH_N_TRANSFER, sc, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "Cannot setup USB transfers\n");
		goto detach;
	}
	ue->ue_sc = sc;
	ue->ue_dev = dev;
	ue->ue_udev = uaa->device;
	ue->ue_mtx = &sc->sc_mtx;
	ue->ue_methods = &ipheth_ue_methods;

	error = ipheth_get_mac_addr(sc);
	if (error) {
		device_printf(dev, "Cannot get MAC address\n");
		goto detach;
	}

	error = uether_ifattach(ue);
	if (error) {
		device_printf(dev, "could not attach interface\n");
		goto detach;
	}
	return (0);			/* success */

detach:
	ipheth_detach(dev);
	return (ENXIO);			/* failure */
}