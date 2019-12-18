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
struct TYPE_2__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; } ;
struct uftdi_softc {int sc_last_lcr; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_bitmode; int /*<<< orphan*/  sc_unit; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENXIO ; 
 int FTDI_SIO_SET_DATA_BITS (int) ; 
 int FTDI_SIO_SET_DATA_PARITY_NONE ; 
 int FTDI_SIO_SET_DATA_STOP_BITS_2 ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UFTDI_BITMODE_NONE ; 
 size_t UFTDI_BULK_DT_RD ; 
 size_t UFTDI_BULK_DT_WR ; 
 int /*<<< orphan*/  UFTDI_N_TRANSFER ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct uftdi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct uftdi_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_use_lsr_txbits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uftdi_callback ; 
 int /*<<< orphan*/  uftdi_config ; 
 int /*<<< orphan*/  uftdi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uftdi_devtype_setup (struct uftdi_softc*,struct usb_attach_arg*) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uftdi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uftdi_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct uftdi_softc *sc = device_get_softc(dev);
	int error;

	DPRINTF("\n");

	sc->sc_udev = uaa->device;
	sc->sc_dev = dev;
	sc->sc_unit = device_get_unit(dev);
	sc->sc_bitmode = UFTDI_BITMODE_NONE;

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "uftdi", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);


	uftdi_devtype_setup(sc, uaa);

	error = usbd_transfer_setup(uaa->device,
	    &uaa->info.bIfaceIndex, sc->sc_xfer, uftdi_config,
	    UFTDI_N_TRANSFER, sc, &sc->sc_mtx);

	if (error) {
		device_printf(dev, "allocating USB "
		    "transfers failed\n");
		goto detach;
	}
	/* clear stall at first run */
	mtx_lock(&sc->sc_mtx);
	usbd_xfer_set_stall(sc->sc_xfer[UFTDI_BULK_DT_WR]);
	usbd_xfer_set_stall(sc->sc_xfer[UFTDI_BULK_DT_RD]);
	mtx_unlock(&sc->sc_mtx);

	/* set a valid "lcr" value */

	sc->sc_last_lcr =
	    (FTDI_SIO_SET_DATA_STOP_BITS_2 |
	    FTDI_SIO_SET_DATA_PARITY_NONE |
	    FTDI_SIO_SET_DATA_BITS(8));

	/* Indicate tx bits in sc_lsr can be used to determine busy vs idle. */
	ucom_use_lsr_txbits(&sc->sc_ucom);

	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &uftdi_callback, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	return (0);			/* success */

detach:
	uftdi_detach(dev);
	return (ENXIO);
}