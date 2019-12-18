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
typedef  int usb_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  wValue; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
typedef  TYPE_1__ usb_device_request_t ;
struct uftdi_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; } ;
struct ucom_softc {struct uftdi_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FTDI_SIO_ERASE_EEPROM ; 
 int UFTDI_CONFIRM_ERASE ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_VENDOR_DEVICE ; 
 int usbd_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uftdi_erase_eeprom(struct ucom_softc *ucom, int confirmation)
{
	struct uftdi_softc *sc = ucom->sc_parent;
	usb_device_request_t req;
	usb_error_t err;

	DPRINTFN(2, "\n");

	/* Small effort to prevent accidental erasure. */
	if (confirmation != UFTDI_CONFIRM_ERASE)
		return (EINVAL);

	req.bmRequestType = UT_WRITE_VENDOR_DEVICE;
	req.bRequest = FTDI_SIO_ERASE_EEPROM;
	USETW(req.wIndex, 0);
	USETW(req.wLength, 0);
	USETW(req.wValue, 0);
	err = usbd_do_request(sc->sc_udev, &sc->sc_mtx, &req, NULL);

	return (err);
}