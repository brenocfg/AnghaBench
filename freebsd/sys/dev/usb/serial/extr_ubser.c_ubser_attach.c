#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct TYPE_3__ {int /*<<< orphan*/  bIfaceIndex; scalar_t__ bIfaceNum; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; } ;
struct ubser_softc {scalar_t__ sc_numser; scalar_t__ sc_tx_size; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_super_ucom; TYPE_2__* sc_ucom; int /*<<< orphan*/  sc_iface_index; scalar_t__ sc_iface_no; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {size_t sc_portno; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 size_t UBSER_BULK_DT_RD ; 
 size_t UBSER_BULK_DT_WR ; 
 int /*<<< orphan*/  UBSER_N_TRANSFER ; 
 scalar_t__ UBSER_UNIT_MAX ; 
 int /*<<< orphan*/  USB_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_VENDOR_INTERFACE ; 
 int /*<<< orphan*/  VENDOR_GET_NUMSER ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct ubser_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubser_callback ; 
 int /*<<< orphan*/  ubser_config ; 
 int /*<<< orphan*/  ubser_detach (int /*<<< orphan*/ ) ; 
 int ucom_attach (int /*<<< orphan*/ *,TYPE_2__*,size_t,struct ubser_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usbd_do_request_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ubser_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_xfer_max_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ubser_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct ubser_softc *sc = device_get_softc(dev);
	struct usb_device_request req;
	uint8_t n;
	int error;

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "ubser", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	sc->sc_iface_no = uaa->info.bIfaceNum;
	sc->sc_iface_index = uaa->info.bIfaceIndex;
	sc->sc_udev = uaa->device;

	/* get number of serials */
	req.bmRequestType = UT_READ_VENDOR_INTERFACE;
	req.bRequest = VENDOR_GET_NUMSER;
	USETW(req.wValue, 0);
	req.wIndex[0] = sc->sc_iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, 1);
	error = usbd_do_request_flags(uaa->device, NULL,
	    &req, &sc->sc_numser,
	    0, NULL, USB_DEFAULT_TIMEOUT);

	if (error || (sc->sc_numser == 0)) {
		device_printf(dev, "failed to get number "
		    "of serial ports: %s\n",
		    usbd_errstr(error));
		goto detach;
	}
	if (sc->sc_numser > UBSER_UNIT_MAX)
		sc->sc_numser = UBSER_UNIT_MAX;

	device_printf(dev, "found %i serials\n", sc->sc_numser);

	error = usbd_transfer_setup(uaa->device, &sc->sc_iface_index,
	    sc->sc_xfer, ubser_config, UBSER_N_TRANSFER, sc, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	sc->sc_tx_size = usbd_xfer_max_len(sc->sc_xfer[UBSER_BULK_DT_WR]);

	if (sc->sc_tx_size == 0) {
		DPRINTFN(0, "invalid tx_size\n");
		goto detach;
	}
	/* initialize port numbers */

	for (n = 0; n < sc->sc_numser; n++) {
		sc->sc_ucom[n].sc_portno = n;
	}

	error = ucom_attach(&sc->sc_super_ucom, sc->sc_ucom,
	    sc->sc_numser, sc, &ubser_callback, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	mtx_lock(&sc->sc_mtx);
	usbd_xfer_set_stall(sc->sc_xfer[UBSER_BULK_DT_WR]);
	usbd_xfer_set_stall(sc->sc_xfer[UBSER_BULK_DT_RD]);
	usbd_transfer_start(sc->sc_xfer[UBSER_BULK_DT_RD]);
	mtx_unlock(&sc->sc_mtx);

	return (0);			/* success */

detach:
	ubser_detach(dev);
	return (ENXIO);			/* failure */
}