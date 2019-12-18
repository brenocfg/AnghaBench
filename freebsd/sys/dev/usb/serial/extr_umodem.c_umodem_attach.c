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
typedef  scalar_t__ uint8_t ;
struct usb_interface_descriptor {scalar_t__ bInterfaceNumber; } ;
struct usb_interface {int dummy; } ;
struct usb_cdc_union_descriptor {int bLength; int* bSlaveInterface; } ;
struct usb_cdc_cm_descriptor {int bLength; int bDataInterface; } ;
struct TYPE_2__ {int bIfaceNum; scalar_t__ bIfaceIndex; } ;
struct usb_attach_arg {scalar_t__ usb_mode; int /*<<< orphan*/  device; TYPE_1__ info; } ;
struct umodem_softc {int sc_ctrl_iface_no; int sc_cm_cap; int sc_acm_cap; int sc_data_iface_no; int sc_cm_over_data; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/ * sc_xfer; scalar_t__* sc_iface_index; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UCDC_ABSTRACT_STATE ; 
 int /*<<< orphan*/  UCDC_DATA_MULTIPLEXED ; 
 int /*<<< orphan*/  UDESCSUB_CDC_CM ; 
 int /*<<< orphan*/  UDESCSUB_CDC_UNION ; 
 int /*<<< orphan*/  UDESC_CS_INTERFACE ; 
 size_t UMODEM_BULK_RD ; 
 size_t UMODEM_BULK_WR ; 
 int /*<<< orphan*/  UMODEM_N_TRANSFER ; 
 int /*<<< orphan*/  UQ_ASSUME_CM_OVER_DATA ; 
 int USB_CDC_ACM_HAS_BREAK ; 
 int USB_CDC_ACM_HAS_FEATURE ; 
 int USB_CDC_CM_OVER_DATA ; 
 scalar_t__ USB_MODE_HOST ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct umodem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct umodem_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucom_set_usb_mode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  umodem_callback ; 
 int /*<<< orphan*/  umodem_config ; 
 int /*<<< orphan*/  umodem_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umodem_find_data_iface (struct usb_attach_arg*,scalar_t__,int*,scalar_t__*) ; 
 int /*<<< orphan*/  umodem_get_caps (struct usb_attach_arg*,int*,int*) ; 
 struct usb_cdc_cm_descriptor* umodem_get_desc (struct usb_attach_arg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int umodem_set_comm_feature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_test_quirk (struct usb_attach_arg*,int /*<<< orphan*/ ) ; 
 struct usb_cdc_union_descriptor* usbd_find_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct usb_interface* usbd_get_iface (int /*<<< orphan*/ ,scalar_t__) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (struct usb_interface*) ; 
 int /*<<< orphan*/  usbd_set_parent_iface (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umodem_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
umodem_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct umodem_softc *sc = device_get_softc(dev);
	struct usb_cdc_cm_descriptor *cmd;
	struct usb_cdc_union_descriptor *cud;
	uint8_t i;
	int error;

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, "umodem", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	sc->sc_ctrl_iface_no = uaa->info.bIfaceNum;
	sc->sc_iface_index[1] = uaa->info.bIfaceIndex;
	sc->sc_udev = uaa->device;

	umodem_get_caps(uaa, &sc->sc_cm_cap, &sc->sc_acm_cap);

	/* get the data interface number */

	cmd = umodem_get_desc(uaa, UDESC_CS_INTERFACE, UDESCSUB_CDC_CM);

	if ((cmd == NULL) || (cmd->bLength < sizeof(*cmd))) {

		cud = usbd_find_descriptor(uaa->device, NULL,
		    uaa->info.bIfaceIndex, UDESC_CS_INTERFACE,
		    0xFF, UDESCSUB_CDC_UNION, 0xFF);

		if ((cud == NULL) || (cud->bLength < sizeof(*cud))) {
			DPRINTF("Missing descriptor. "
			    "Assuming data interface is next.\n");
			if (sc->sc_ctrl_iface_no == 0xFF) {
				goto detach;
			} else {
				uint8_t class_match = 0;

				/* set default interface number */
				sc->sc_data_iface_no = 0xFF;

				/* try to find the data interface backwards */
				umodem_find_data_iface(uaa,
				    uaa->info.bIfaceIndex - 1,
				    &sc->sc_data_iface_no, &class_match);

				/* try to find the data interface forwards */
				umodem_find_data_iface(uaa,
				    uaa->info.bIfaceIndex + 1,
				    &sc->sc_data_iface_no, &class_match);

				/* check if nothing was found */
				if (sc->sc_data_iface_no == 0xFF)
					goto detach;
			}
		} else {
			sc->sc_data_iface_no = cud->bSlaveInterface[0];
		}
	} else {
		sc->sc_data_iface_no = cmd->bDataInterface;
	}

	device_printf(dev, "data interface %d, has %sCM over "
	    "data, has %sbreak\n",
	    sc->sc_data_iface_no,
	    sc->sc_cm_cap & USB_CDC_CM_OVER_DATA ? "" : "no ",
	    sc->sc_acm_cap & USB_CDC_ACM_HAS_BREAK ? "" : "no ");

	/* get the data interface too */

	for (i = 0;; i++) {
		struct usb_interface *iface;
		struct usb_interface_descriptor *id;

		iface = usbd_get_iface(uaa->device, i);

		if (iface) {

			id = usbd_get_interface_descriptor(iface);

			if (id && (id->bInterfaceNumber == sc->sc_data_iface_no)) {
				sc->sc_iface_index[0] = i;
				usbd_set_parent_iface(uaa->device, i, uaa->info.bIfaceIndex);
				break;
			}
		} else {
			device_printf(dev, "no data interface\n");
			goto detach;
		}
	}

	if (usb_test_quirk(uaa, UQ_ASSUME_CM_OVER_DATA)) {
		sc->sc_cm_over_data = 1;
	} else {
		if (sc->sc_cm_cap & USB_CDC_CM_OVER_DATA) {
			if (sc->sc_acm_cap & USB_CDC_ACM_HAS_FEATURE) {

				error = umodem_set_comm_feature
				(uaa->device, sc->sc_ctrl_iface_no,
				 UCDC_ABSTRACT_STATE, UCDC_DATA_MULTIPLEXED);

				/* ignore any errors */
			}
			sc->sc_cm_over_data = 1;
		}
	}
	error = usbd_transfer_setup(uaa->device,
	    sc->sc_iface_index, sc->sc_xfer,
	    umodem_config, UMODEM_N_TRANSFER,
	    sc, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "Can't setup transfer\n");
		goto detach;
	}

	/* clear stall at first run, if USB host mode */
	if (uaa->usb_mode == USB_MODE_HOST) {
		mtx_lock(&sc->sc_mtx);
		usbd_xfer_set_stall(sc->sc_xfer[UMODEM_BULK_WR]);
		usbd_xfer_set_stall(sc->sc_xfer[UMODEM_BULK_RD]);
		mtx_unlock(&sc->sc_mtx);
	}

	ucom_set_usb_mode(&sc->sc_super_ucom, uaa->usb_mode);

	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &umodem_callback, &sc->sc_mtx);
	if (error) {
		device_printf(dev, "Can't attach com\n");
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	return (0);

detach:
	umodem_detach(dev);
	return (ENXIO);
}