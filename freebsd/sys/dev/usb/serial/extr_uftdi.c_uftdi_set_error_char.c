#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wValue; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
typedef  TYPE_2__ usb_device_request_t ;
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  sc_portno; } ;
struct uftdi_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; TYPE_1__ sc_ucom; } ;
struct ucom_softc {struct uftdi_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  FTDI_SIO_SET_ERROR_CHAR ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UT_WRITE_VENDOR_DEVICE ; 
 int usbd_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uftdi_set_error_char(struct ucom_softc *ucom, int echar)
{
	struct uftdi_softc *sc = ucom->sc_parent;
	usb_device_request_t req;
	uint8_t enable;

	DPRINTFN(2, "\n");

	enable = (echar == -1) ? 0 : 1;

	req.bmRequestType = UT_WRITE_VENDOR_DEVICE;
	req.bRequest = FTDI_SIO_SET_ERROR_CHAR;

	USETW(req.wIndex, sc->sc_ucom.sc_portno);
	USETW(req.wLength, 0);
	USETW2(req.wValue, enable, echar & 0xff);

	return (usbd_do_request(sc->sc_udev, &sc->sc_mtx, &req, NULL));
}