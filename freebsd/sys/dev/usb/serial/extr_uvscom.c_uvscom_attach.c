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
struct uvscom_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_line; int /*<<< orphan*/  sc_iface_index; int /*<<< orphan*/  sc_iface_no; int /*<<< orphan*/  sc_udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bIfaceNum; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 size_t UVSCOM_BULK_DT_RD ; 
 size_t UVSCOM_BULK_DT_WR ; 
 int /*<<< orphan*/  UVSCOM_IFACE_INDEX ; 
 size_t UVSCOM_INTR_DT_RD ; 
 int /*<<< orphan*/  UVSCOM_LINE_INIT ; 
 int /*<<< orphan*/  UVSCOM_N_TRANSFER ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct uvscom_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct uvscom_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uvscom_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvscom_callback ; 
 int /*<<< orphan*/  uvscom_config ; 
 int /*<<< orphan*/  uvscom_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uvscom_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct uvscom_softc *sc = device_get_softc(dev);
	int error;

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "uvscom", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	sc->sc_udev = uaa->device;

	DPRINTF("sc=%p\n", sc);

	sc->sc_iface_no = uaa->info.bIfaceNum;
	sc->sc_iface_index = UVSCOM_IFACE_INDEX;

	error = usbd_transfer_setup(uaa->device, &sc->sc_iface_index,
	    sc->sc_xfer, uvscom_config, UVSCOM_N_TRANSFER, sc, &sc->sc_mtx);

	if (error) {
		DPRINTF("could not allocate all USB transfers!\n");
		goto detach;
	}
	sc->sc_line = UVSCOM_LINE_INIT;

	/* clear stall at first run */
	mtx_lock(&sc->sc_mtx);
	usbd_xfer_set_stall(sc->sc_xfer[UVSCOM_BULK_DT_WR]);
	usbd_xfer_set_stall(sc->sc_xfer[UVSCOM_BULK_DT_RD]);
	mtx_unlock(&sc->sc_mtx);

	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &uvscom_callback, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	/* start interrupt pipe */
	mtx_lock(&sc->sc_mtx);
	usbd_transfer_start(sc->sc_xfer[UVSCOM_INTR_DT_RD]);
	mtx_unlock(&sc->sc_mtx);

	return (0);

detach:
	uvscom_detach(dev);
	return (ENXIO);
}