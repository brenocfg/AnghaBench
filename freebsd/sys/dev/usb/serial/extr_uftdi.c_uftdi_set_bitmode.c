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
struct uftdi_softc {int sc_bitmode; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; TYPE_1__ sc_ucom; } ;
struct ucom_softc {struct uftdi_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  FTDI_SIO_SET_BITMODE ; 
 int UFTDI_BITMODE_NONE ; 
 int USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UT_WRITE_VENDOR_DEVICE ; 
 int usbd_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uftdi_set_bitmode(struct ucom_softc *ucom, uint8_t bitmode, uint8_t iomask)
{
	struct uftdi_softc *sc = ucom->sc_parent;
	usb_device_request_t req;
	int rv;

	DPRINTFN(2, "\n");

	req.bmRequestType = UT_WRITE_VENDOR_DEVICE;
	req.bRequest = FTDI_SIO_SET_BITMODE;

	USETW(req.wIndex, sc->sc_ucom.sc_portno);
	USETW(req.wLength, 0);

	if (bitmode == UFTDI_BITMODE_NONE)
	    USETW2(req.wValue, 0, 0);
	else
	    USETW2(req.wValue, (1 << bitmode), iomask);

	rv = usbd_do_request(sc->sc_udev, &sc->sc_mtx, &req, NULL);
	if (rv == USB_ERR_NORMAL_COMPLETION)
		sc->sc_bitmode = bitmode;

	return (rv);
}