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
struct usb_ether {int /*<<< orphan*/ * ue_methods; int /*<<< orphan*/ * ue_mtx; int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; struct smsc_softc* ue_sc; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct smsc_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_flags; struct usb_ether sc_ue; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  SMSC_IFACE_IDX ; 
 int /*<<< orphan*/  SMSC_N_TRANSFER ; 
 int /*<<< orphan*/  USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct smsc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc_config ; 
 int /*<<< orphan*/  smsc_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc_ue_methods ; 
 int uether_ifattach (struct usb_ether*) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smsc_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smsc_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct smsc_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;
	uint8_t iface_index;
	int err;

	sc->sc_flags = USB_GET_DRIVER_INFO(uaa);

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	/* Setup the endpoints for the SMSC LAN95xx device(s) */
	iface_index = SMSC_IFACE_IDX;
	err = usbd_transfer_setup(uaa->device, &iface_index, sc->sc_xfer,
	                          smsc_config, SMSC_N_TRANSFER, sc, &sc->sc_mtx);
	if (err) {
		device_printf(dev, "error: allocating USB transfers failed\n");
		goto detach;
	}

	ue->ue_sc = sc;
	ue->ue_dev = dev;
	ue->ue_udev = uaa->device;
	ue->ue_mtx = &sc->sc_mtx;
	ue->ue_methods = &smsc_ue_methods;

	err = uether_ifattach(ue);
	if (err) {
		device_printf(dev, "error: could not attach interface\n");
		goto detach;
	}
	return (0);			/* success */

detach:
	smsc_detach(dev);
	return (ENXIO);		/* failure */
}