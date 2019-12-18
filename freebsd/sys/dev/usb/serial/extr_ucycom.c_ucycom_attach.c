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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  bIfaceNum; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; } ;
struct ucycom_softc {scalar_t__ sc_model; int sc_flen; int sc_ilen; int sc_olen; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_iface_no; int /*<<< orphan*/  sc_oid; int /*<<< orphan*/  sc_iid; int /*<<< orphan*/  sc_fid; int /*<<< orphan*/  sc_udev; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  UCYCOM_IFACE_INDEX ; 
 int UCYCOM_MAX_IOLEN ; 
 int /*<<< orphan*/  UCYCOM_N_TRANSFER ; 
 scalar_t__ USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct ucycom_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_feature ; 
 int /*<<< orphan*/  hid_input ; 
 int /*<<< orphan*/  hid_output ; 
 void* hid_report_size (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct ucycom_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucycom_callback ; 
 int /*<<< orphan*/  ucycom_config ; 
 int /*<<< orphan*/  ucycom_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 
 scalar_t__ usbd_req_get_hid_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucycom_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ucycom_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct ucycom_softc *sc = device_get_softc(dev);
	void *urd_ptr = NULL;
	int32_t error;
	uint16_t urd_len;
	uint8_t iface_index;

	sc->sc_udev = uaa->device;

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "ucycom", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	DPRINTF("\n");

	/* get chip model */
	sc->sc_model = USB_GET_DRIVER_INFO(uaa);
	if (sc->sc_model == 0) {
		device_printf(dev, "unsupported device\n");
		goto detach;
	}
	device_printf(dev, "Cypress CY7C%X USB to RS232 bridge\n", sc->sc_model);

	/* get report descriptor */

	error = usbd_req_get_hid_desc(uaa->device, NULL,
	    &urd_ptr, &urd_len, M_USBDEV,
	    UCYCOM_IFACE_INDEX);

	if (error) {
		device_printf(dev, "failed to get report "
		    "descriptor: %s\n",
		    usbd_errstr(error));
		goto detach;
	}
	/* get report sizes */

	sc->sc_flen = hid_report_size(urd_ptr, urd_len, hid_feature, &sc->sc_fid);
	sc->sc_ilen = hid_report_size(urd_ptr, urd_len, hid_input, &sc->sc_iid);
	sc->sc_olen = hid_report_size(urd_ptr, urd_len, hid_output, &sc->sc_oid);

	if ((sc->sc_ilen > UCYCOM_MAX_IOLEN) || (sc->sc_ilen < 1) ||
	    (sc->sc_olen > UCYCOM_MAX_IOLEN) || (sc->sc_olen < 2) ||
	    (sc->sc_flen > UCYCOM_MAX_IOLEN) || (sc->sc_flen < 5)) {
		device_printf(dev, "invalid report size i=%d, o=%d, f=%d, max=%d\n",
		    sc->sc_ilen, sc->sc_olen, sc->sc_flen,
		    UCYCOM_MAX_IOLEN);
		goto detach;
	}
	sc->sc_iface_no = uaa->info.bIfaceNum;

	iface_index = UCYCOM_IFACE_INDEX;
	error = usbd_transfer_setup(uaa->device, &iface_index,
	    sc->sc_xfer, ucycom_config, UCYCOM_N_TRANSFER,
	    sc, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "allocating USB "
		    "transfers failed\n");
		goto detach;
	}
	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &ucycom_callback, &sc->sc_mtx);
	if (error) {
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	if (urd_ptr) {
		free(urd_ptr, M_USBDEV);
	}

	return (0);			/* success */

detach:
	if (urd_ptr) {
		free(urd_ptr, M_USBDEV);
	}
	ucycom_detach(dev);
	return (ENXIO);
}