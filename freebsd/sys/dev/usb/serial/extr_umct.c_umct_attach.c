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
typedef  int uint16_t ;
struct usb_xfer {int dummy; } ;
struct TYPE_2__ {scalar_t__ idProduct; int /*<<< orphan*/  bIfaceNum; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; } ;
struct umct_softc {int sc_swap_cb; int sc_obufsize; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; struct usb_xfer** sc_xfer; int /*<<< orphan*/  sc_iface_no; int /*<<< orphan*/  sc_unit; int /*<<< orphan*/  sc_udev; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 size_t UMCT_BULK_DT_RD ; 
 size_t UMCT_BULK_DT_WR ; 
 int /*<<< orphan*/  UMCT_IFACE_INDEX ; 
 size_t UMCT_INTR_DT_RD ; 
 int /*<<< orphan*/  UMCT_N_TRANSFER ; 
 scalar_t__ USB_PRODUCT_MCT_SITECOM_USB232 ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct umct_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct umct_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umct_callback ; 
 int /*<<< orphan*/  umct_config ; 
 int /*<<< orphan*/  umct_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_xfer**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umct_softc*,int /*<<< orphan*/ *) ; 
 int usbd_xfer_max_framelen (struct usb_xfer*) ; 
 int usbd_xfer_max_len (struct usb_xfer*) ; 

__attribute__((used)) static int
umct_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct umct_softc *sc = device_get_softc(dev);
	int32_t error;
	uint16_t maxp;
	uint8_t iface_index;

	sc->sc_udev = uaa->device;
	sc->sc_unit = device_get_unit(dev);

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "umct", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	sc->sc_iface_no = uaa->info.bIfaceNum;

	iface_index = UMCT_IFACE_INDEX;
	error = usbd_transfer_setup(uaa->device, &iface_index,
	    sc->sc_xfer, umct_config, UMCT_N_TRANSFER, sc, &sc->sc_mtx);

	if (error) {
		device_printf(dev, "allocating USB "
		    "transfers failed\n");
		goto detach;
	}

	/*
	 * The real bulk-in endpoint is also marked as an interrupt.
	 * The only way to differentiate it from the real interrupt
	 * endpoint is to look at the wMaxPacketSize field.
	 */
	maxp = usbd_xfer_max_framelen(sc->sc_xfer[UMCT_BULK_DT_RD]);
	if (maxp == 0x2) {

		/* guessed wrong - switch around endpoints */

		struct usb_xfer *temp = sc->sc_xfer[UMCT_INTR_DT_RD];

		sc->sc_xfer[UMCT_INTR_DT_RD] = sc->sc_xfer[UMCT_BULK_DT_RD];
		sc->sc_xfer[UMCT_BULK_DT_RD] = temp;
		sc->sc_swap_cb = 1;
	}

	sc->sc_obufsize = usbd_xfer_max_len(sc->sc_xfer[UMCT_BULK_DT_WR]);

	if (uaa->info.idProduct == USB_PRODUCT_MCT_SITECOM_USB232) {
		if (sc->sc_obufsize > 16) {
			sc->sc_obufsize = 16;
		}
	}
	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &umct_callback, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	return (0);			/* success */

detach:
	umct_detach(dev);
	return (ENXIO);			/* failure */
}