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
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct umoscom_softc {int sc_mcr; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 size_t UMOSCOM_BULK_DT_RD ; 
 size_t UMOSCOM_BULK_DT_WR ; 
 int /*<<< orphan*/  UMOSCOM_IFACE_INDEX ; 
 int /*<<< orphan*/  UMOSCOM_N_TRANSFER ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct umoscom_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct umoscom_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umoscom_callback ; 
 int /*<<< orphan*/  umoscom_config_data ; 
 int /*<<< orphan*/  umoscom_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umoscom_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
umoscom_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct umoscom_softc *sc = device_get_softc(dev);
	int error;
	uint8_t iface_index;

	sc->sc_udev = uaa->device;
	sc->sc_mcr = 0x08;		/* enable interrupts */

	/* XXX the device doesn't provide any ID string, so set a static one */
	device_set_desc(dev, "MOSCHIP USB Serial Port Adapter");
	device_printf(dev, "<MOSCHIP USB Serial Port Adapter>\n");

	mtx_init(&sc->sc_mtx, "umoscom", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	iface_index = UMOSCOM_IFACE_INDEX;
	error = usbd_transfer_setup(uaa->device, &iface_index,
	    sc->sc_xfer, umoscom_config_data,
	    UMOSCOM_N_TRANSFER, sc, &sc->sc_mtx);

	if (error) {
		goto detach;
	}
	/* clear stall at first run */
	mtx_lock(&sc->sc_mtx);
	usbd_xfer_set_stall(sc->sc_xfer[UMOSCOM_BULK_DT_WR]);
	usbd_xfer_set_stall(sc->sc_xfer[UMOSCOM_BULK_DT_RD]);
	mtx_unlock(&sc->sc_mtx);

	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &umoscom_callback, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	return (0);

detach:
	device_printf(dev, "attach error: %s\n", usbd_errstr(error));
	umoscom_detach(dev);
	return (ENXIO);
}