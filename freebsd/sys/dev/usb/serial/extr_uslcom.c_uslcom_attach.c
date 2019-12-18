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
struct uslcom_softc {int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_partnum; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_iface_no; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_watchdog; } ;
struct TYPE_2__ {int /*<<< orphan*/  bIfaceIndex; int /*<<< orphan*/  bIfaceNum; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 size_t USLCOM_BULK_DT_RD ; 
 size_t USLCOM_BULK_DT_WR ; 
 int /*<<< orphan*/  USLCOM_N_TRANSFER ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct uslcom_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct uslcom_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uslcom_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uslcom_callback ; 
 int /*<<< orphan*/  uslcom_config ; 
 int /*<<< orphan*/  uslcom_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uslcom_get_partnum (struct uslcom_softc*) ; 

__attribute__((used)) static int
uslcom_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct uslcom_softc *sc = device_get_softc(dev);
	int error;

	DPRINTFN(11, "\n");

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "uslcom", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);
	usb_callout_init_mtx(&sc->sc_watchdog, &sc->sc_mtx, 0);

	sc->sc_udev = uaa->device;
	/* use the interface number from the USB interface descriptor */
	sc->sc_iface_no = uaa->info.bIfaceNum;

	error = usbd_transfer_setup(uaa->device,
	    &uaa->info.bIfaceIndex, sc->sc_xfer, uslcom_config,
	    USLCOM_N_TRANSFER, sc, &sc->sc_mtx);
	if (error) {
		DPRINTF("one or more missing USB endpoints, "
		    "error=%s\n", usbd_errstr(error));
		goto detach;
	}
	/* clear stall at first run */
	mtx_lock(&sc->sc_mtx);
	usbd_xfer_set_stall(sc->sc_xfer[USLCOM_BULK_DT_WR]);
	usbd_xfer_set_stall(sc->sc_xfer[USLCOM_BULK_DT_RD]);
	mtx_unlock(&sc->sc_mtx);

	sc->sc_partnum = uslcom_get_partnum(sc);

	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &uslcom_callback, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	return (0);

detach:
	uslcom_detach(dev);
	return (ENXIO);
}