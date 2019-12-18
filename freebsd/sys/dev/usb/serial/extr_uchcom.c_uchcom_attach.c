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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int idProduct; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; } ;
struct uchcom_softc {int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 size_t UCHCOM_BULK_DT_RD ; 
 size_t UCHCOM_BULK_DT_WR ; 
 int /*<<< orphan*/  UCHCOM_IFACE_INDEX ; 
 int /*<<< orphan*/  UCHCOM_N_TRANSFER ; 
#define  USB_PRODUCT_WCH2_CH341SER 129 
#define  USB_PRODUCT_WCH2_CH341SER_2 128 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct uchcom_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uchcom_callback ; 
 int /*<<< orphan*/  uchcom_config_data ; 
 int /*<<< orphan*/  uchcom_detach (int /*<<< orphan*/ ) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct uchcom_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uchcom_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uchcom_attach(device_t dev)
{
	struct uchcom_softc *sc = device_get_softc(dev);
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	int error;
	uint8_t iface_index;

	DPRINTFN(11, "\n");

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "uchcom", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	sc->sc_udev = uaa->device;

	switch (uaa->info.idProduct) {
	case USB_PRODUCT_WCH2_CH341SER:
		device_printf(dev, "CH340 detected\n");
		break;
	case USB_PRODUCT_WCH2_CH341SER_2:
		device_printf(dev, "CH341 detected\n");
		break;
	default:
		device_printf(dev, "New CH340/CH341 product 0x%04x detected\n",
		    uaa->info.idProduct);
		break;
	}

	iface_index = UCHCOM_IFACE_INDEX;
	error = usbd_transfer_setup(uaa->device,
	    &iface_index, sc->sc_xfer, uchcom_config_data,
	    UCHCOM_N_TRANSFER, sc, &sc->sc_mtx);

	if (error) {
		DPRINTF("one or more missing USB endpoints, "
		    "error=%s\n", usbd_errstr(error));
		goto detach;
	}

	/* clear stall at first run */
	mtx_lock(&sc->sc_mtx);
	usbd_xfer_set_stall(sc->sc_xfer[UCHCOM_BULK_DT_WR]);
	usbd_xfer_set_stall(sc->sc_xfer[UCHCOM_BULK_DT_RD]);
	mtx_unlock(&sc->sc_mtx);

	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &uchcom_callback, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	return (0);

detach:
	uchcom_detach(dev);
	return (ENXIO);
}