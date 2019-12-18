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
struct usb_ether {int /*<<< orphan*/ * ue_methods; int /*<<< orphan*/ * ue_mtx; int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; struct muge_softc* ue_sc; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct muge_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; struct usb_ether sc_ue; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int MUGE_FLAG_INIT_DONE ; 
 int /*<<< orphan*/  MUGE_IFACE_IDX ; 
 int /*<<< orphan*/  MUGE_N_TRANSFER ; 
 int USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct muge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  muge_config ; 
 int /*<<< orphan*/  muge_ue_methods ; 
 int uether_ifattach (struct usb_ether*) ; 
 int /*<<< orphan*/  uether_ifattach_wait (struct usb_ether*) ; 
 int /*<<< orphan*/  uether_ifdetach (struct usb_ether*) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct muge_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
muge_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct muge_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;
	uint8_t iface_index;
	int err;

	sc->sc_flags = USB_GET_DRIVER_INFO(uaa);

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	/* Setup the endpoints for the Microchip LAN78xx device. */
	iface_index = MUGE_IFACE_IDX;
	err = usbd_transfer_setup(uaa->device, &iface_index, sc->sc_xfer,
	    muge_config, MUGE_N_TRANSFER, sc, &sc->sc_mtx);
	if (err) {
		device_printf(dev, "error: allocating USB transfers failed\n");
		goto err;
	}

	ue->ue_sc = sc;
	ue->ue_dev = dev;
	ue->ue_udev = uaa->device;
	ue->ue_mtx = &sc->sc_mtx;
	ue->ue_methods = &muge_ue_methods;

	err = uether_ifattach(ue);
	if (err) {
		device_printf(dev, "error: could not attach interface\n");
		goto err_usbd;
	}

	/* Wait for lan78xx_chip_init from post-attach callback to complete. */
	uether_ifattach_wait(ue);
	if (!(sc->sc_flags & MUGE_FLAG_INIT_DONE))
		goto err_attached;

	return (0);

err_attached:
	uether_ifdetach(ue);
err_usbd:
	usbd_transfer_unsetup(sc->sc_xfer, MUGE_N_TRANSFER);
err:
	mtx_destroy(&sc->sc_mtx);
	return (ENXIO);
}