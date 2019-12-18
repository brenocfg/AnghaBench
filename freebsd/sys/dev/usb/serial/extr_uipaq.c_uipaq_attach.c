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
typedef  int uint8_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct uipaq_softc {int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int UCDC_LINE_DTR ; 
 int /*<<< orphan*/  UCDC_SET_CONTROL_LINE_STATE ; 
 size_t UIPAQ_BULK_DT_RD ; 
 size_t UIPAQ_BULK_DT_WR ; 
 int UIPAQ_IFACE_INDEX ; 
 int /*<<< orphan*/  UIPAQ_N_TRANSFER ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct uipaq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct uipaq_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uipaq_callback ; 
 int /*<<< orphan*/  uipaq_config_data ; 
 int /*<<< orphan*/  uipaq_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 
 int usbd_do_request_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uipaq_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uipaq_attach(device_t dev)
{
	struct usb_device_request req;
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct uipaq_softc *sc = device_get_softc(dev);
	int error;
	uint8_t iface_index;
	uint8_t i;

	sc->sc_udev = uaa->device;

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "uipaq", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	/*
	 * Send magic bytes, cribbed from Linux ipaq driver that
	 * claims to have sniffed them from Win98. Wait for driver to
	 * become ready on device side?
	 */
	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = UCDC_SET_CONTROL_LINE_STATE;
	USETW(req.wValue, UCDC_LINE_DTR);
	USETW(req.wIndex, 0x0);
	USETW(req.wLength, 0);
	for (i = 0; i != 64; i++) {
		error =
		    usbd_do_request_flags(uaa->device, NULL, &req,
		    NULL, 0, NULL, 100);
		if (error == 0)
			break;
		usb_pause_mtx(NULL, hz / 10);
	}

	iface_index = UIPAQ_IFACE_INDEX;
	error = usbd_transfer_setup(uaa->device, &iface_index,
	    sc->sc_xfer, uipaq_config_data,
	    UIPAQ_N_TRANSFER, sc, &sc->sc_mtx);

	if (error) {
		goto detach;
	}
	/* clear stall at first run */
	mtx_lock(&sc->sc_mtx);
	usbd_xfer_set_stall(sc->sc_xfer[UIPAQ_BULK_DT_WR]);
	usbd_xfer_set_stall(sc->sc_xfer[UIPAQ_BULK_DT_RD]);
	mtx_unlock(&sc->sc_mtx);

	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &uipaq_callback, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	return (0);

detach:
	uipaq_detach(dev);
	return (ENXIO);
}