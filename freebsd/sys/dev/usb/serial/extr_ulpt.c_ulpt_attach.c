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
typedef  int uint8_t ;
struct usb_interface_descriptor {scalar_t__ bDescriptorType; int bLength; scalar_t__ bInterfaceNumber; scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; int /*<<< orphan*/  bAlternateSetting; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_config_descriptor {int bConfigurationValue; } ;
struct TYPE_2__ {int bIfaceIndex; scalar_t__ bIfaceNum; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; int /*<<< orphan*/  iface; } ;
struct ulpt_softc {scalar_t__ sc_iface_no; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_fifo_noreset; int /*<<< orphan*/  sc_fifo; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_watchdog; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,struct ulpt_softc*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 scalar_t__ UDESC_INTERFACE ; 
 scalar_t__ UICLASS_PRINTER ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ UIPROTO_PRINTER_BI ; 
 scalar_t__ UISUBCLASS_PRINTER ; 
 int /*<<< orphan*/  ULPT_N_TRANSFER ; 
 int /*<<< orphan*/  UR_GET_DEVICE_ID ; 
 int /*<<< orphan*/  USB_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  USB_SHORT_XFER_OK ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USETW2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_READ_CLASS_INTERFACE ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ulpt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int* devinfo ; 
 int /*<<< orphan*/  ieee1284_print_id (int*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ulpt_config ; 
 int /*<<< orphan*/  ulpt_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulpt_fifo_methods ; 
 int /*<<< orphan*/  ulpt_watchdog (struct ulpt_softc*) ; 
 int /*<<< orphan*/  unlpt_fifo_methods ; 
 int /*<<< orphan*/  usb_callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_desc_foreach (struct usb_config_descriptor*,void*) ; 
 int usb_fifo_attach (int /*<<< orphan*/ ,struct ulpt_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usbd_do_request_flags (int /*<<< orphan*/ ,struct usb_device_request*,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int usbd_errstr (int) ; 
 struct usb_config_descriptor* usbd_get_config_descriptor (int /*<<< orphan*/ ) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (int /*<<< orphan*/ ) ; 
 int usbd_set_alt_interface_index (int /*<<< orphan*/ ,int,int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ulpt_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ulpt_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct ulpt_softc *sc = device_get_softc(dev);
	struct usb_interface_descriptor *id;
	int unit = device_get_unit(dev);
	int error;
	uint8_t iface_index = uaa->info.bIfaceIndex;
	uint8_t alt_index;

	DPRINTFN(11, "sc=%p\n", sc);

	sc->sc_dev = dev;
	sc->sc_udev = uaa->device;

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, "ulpt lock", NULL, MTX_DEF | MTX_RECURSE);

	usb_callout_init_mtx(&sc->sc_watchdog, &sc->sc_mtx, 0);

	/* search through all the descriptors looking for bidir mode */

	id = usbd_get_interface_descriptor(uaa->iface);
	alt_index = 0xFF;
	while (1) {
		if (id == NULL) {
			break;
		}
		if ((id->bDescriptorType == UDESC_INTERFACE) &&
		    (id->bLength >= sizeof(*id))) {
			if (id->bInterfaceNumber != uaa->info.bIfaceNum) {
				break;
			} else {
				alt_index++;
				if ((id->bInterfaceClass == UICLASS_PRINTER) &&
				    (id->bInterfaceSubClass == UISUBCLASS_PRINTER) &&
				    (id->bInterfaceProtocol == UIPROTO_PRINTER_BI)) {
					goto found;
				}
			}
		}
		id = (void *)usb_desc_foreach(
		    usbd_get_config_descriptor(uaa->device), (void *)id);
	}
	goto detach;

found:

	DPRINTF("setting alternate "
	    "config number: %d\n", alt_index);

	if (alt_index) {

		error = usbd_set_alt_interface_index
		    (uaa->device, iface_index, alt_index);

		if (error) {
			DPRINTF("could not set alternate "
			    "config, error=%s\n", usbd_errstr(error));
			goto detach;
		}
	}
	sc->sc_iface_no = id->bInterfaceNumber;

	error = usbd_transfer_setup(uaa->device, &iface_index,
	    sc->sc_xfer, ulpt_config, ULPT_N_TRANSFER,
	    sc, &sc->sc_mtx);
	if (error) {
		DPRINTF("error=%s\n", usbd_errstr(error));
		goto detach;
	}
	device_printf(sc->sc_dev, "using bi-directional mode\n");

#if 0
/*
 * This code is disabled because for some mysterious reason it causes
 * printing not to work.  But only sometimes, and mostly with
 * UHCI and less often with OHCI.  *sigh*
 */
	{
		struct usb_config_descriptor *cd = usbd_get_config_descriptor(dev);
		struct usb_device_request req;
		int len, alen;

		req.bmRequestType = UT_READ_CLASS_INTERFACE;
		req.bRequest = UR_GET_DEVICE_ID;
		USETW(req.wValue, cd->bConfigurationValue);
		USETW2(req.wIndex, id->bInterfaceNumber, id->bAlternateSetting);
		USETW(req.wLength, sizeof devinfo - 1);
		error = usbd_do_request_flags(dev, &req, devinfo, USB_SHORT_XFER_OK,
		    &alen, USB_DEFAULT_TIMEOUT);
		if (error) {
			device_printf(sc->sc_dev, "cannot get device id\n");
		} else if (alen <= 2) {
			device_printf(sc->sc_dev, "empty device id, no "
			    "printer connected?\n");
		} else {
			/* devinfo now contains an IEEE-1284 device ID */
			len = ((devinfo[0] & 0xff) << 8) | (devinfo[1] & 0xff);
			if (len > sizeof devinfo - 3)
				len = sizeof devinfo - 3;
			devinfo[len] = 0;
			printf("%s: device id <", device_get_nameunit(sc->sc_dev));
			ieee1284_print_id(devinfo + 2);
			printf(">\n");
		}
	}
#endif

	error = usb_fifo_attach(uaa->device, sc, &sc->sc_mtx,
	    &ulpt_fifo_methods, &sc->sc_fifo,
	    unit, -1, uaa->info.bIfaceIndex,
	    UID_ROOT, GID_OPERATOR, 0644);
	if (error) {
		goto detach;
	}
	error = usb_fifo_attach(uaa->device, sc, &sc->sc_mtx,
	    &unlpt_fifo_methods, &sc->sc_fifo_noreset,
	    unit, -1, uaa->info.bIfaceIndex,
	    UID_ROOT, GID_OPERATOR, 0644);
	if (error) {
		goto detach;
	}
	/* start reading of status */

	mtx_lock(&sc->sc_mtx);
	ulpt_watchdog(sc);
	mtx_unlock(&sc->sc_mtx);
	return (0);

detach:
	ulpt_detach(dev);
	return (ENOMEM);
}