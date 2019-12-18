#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  wValue; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
typedef  TYPE_1__ usb_device_request_t ;
typedef  size_t uint16_t ;
struct uftdi_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; } ;
struct uftdi_eeio {int offset; int length; int /*<<< orphan*/ * data; } ;
struct ucom_softc {struct uftdi_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FTDI_SIO_READ_EEPROM ; 
 scalar_t__ USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_VENDOR_DEVICE ; 
 scalar_t__ usbd_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uftdi_read_eeprom(struct ucom_softc *ucom, struct uftdi_eeio *eeio)
{
	struct uftdi_softc *sc = ucom->sc_parent;
	usb_device_request_t req;
	usb_error_t err;
	uint16_t widx, wlength, woffset;

	DPRINTFN(3, "\n");

	/* Offset and length must both be evenly divisible by two. */
	if ((eeio->offset | eeio->length) & 0x01)
		return (EINVAL);

	woffset = eeio->offset / 2U;
	wlength = eeio->length / 2U;
	for (widx = 0; widx < wlength; widx++) {
		req.bmRequestType = UT_READ_VENDOR_DEVICE;
		req.bRequest = FTDI_SIO_READ_EEPROM;
		USETW(req.wIndex, widx + woffset);
		USETW(req.wLength, 2);
		USETW(req.wValue, 0);
		err = usbd_do_request(sc->sc_udev, &sc->sc_mtx, &req,
		    &eeio->data[widx]);
		if (err != USB_ERR_NORMAL_COMPLETION)
			return (err);
	}
	return (USB_ERR_NORMAL_COMPLETION);
}