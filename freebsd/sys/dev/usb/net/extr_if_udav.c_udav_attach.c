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
struct usb_ether {int /*<<< orphan*/ * ue_mtx; int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; struct udav_softc* ue_sc; int /*<<< orphan*/ * ue_methods; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct udav_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; struct usb_ether sc_ue; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int UDAV_FLAG_LINK ; 
 int UDAV_FLAG_NO_PHY ; 
 int /*<<< orphan*/  UDAV_IFACE_INDEX ; 
 int /*<<< orphan*/  UDAV_N_TRANSFER ; 
 int USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct udav_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udav_config ; 
 int /*<<< orphan*/  udav_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udav_ue_methods ; 
 int /*<<< orphan*/  udav_ue_methods_nophy ; 
 int uether_ifattach (struct usb_ether*) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udav_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
udav_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct udav_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;
	uint8_t iface_index;
	int error;

	sc->sc_flags = USB_GET_DRIVER_INFO(uaa);

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	iface_index = UDAV_IFACE_INDEX;
	error = usbd_transfer_setup(uaa->device, &iface_index,
	    sc->sc_xfer, udav_config, UDAV_N_TRANSFER, sc, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "allocating USB transfers failed\n");
		goto detach;
	}

	/*
	 * The JP1082 has an unusable PHY and provides no link information.
	 */
	if (sc->sc_flags & UDAV_FLAG_NO_PHY) {
		ue->ue_methods = &udav_ue_methods_nophy;
		sc->sc_flags |= UDAV_FLAG_LINK;
	} else {
		ue->ue_methods = &udav_ue_methods;
	}

	ue->ue_sc = sc;
	ue->ue_dev = dev;
	ue->ue_udev = uaa->device;
	ue->ue_mtx = &sc->sc_mtx;

	error = uether_ifattach(ue);
	if (error) {
		device_printf(dev, "could not attach interface\n");
		goto detach;
	}

	return (0);			/* success */

detach:
	udav_detach(dev);
	return (ENXIO);			/* failure */
}