#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; scalar_t__* wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct ucom_softc {scalar_t__ sc_portno; struct ubser_softc* sc_parent; } ;
struct ubser_softc {int /*<<< orphan*/  sc_udev; scalar_t__ sc_iface_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_READ_VENDOR_INTERFACE ; 
 int /*<<< orphan*/  VENDOR_SET_BREAK ; 
 scalar_t__ ucom_cfg_do_request (int /*<<< orphan*/ ,struct ucom_softc*,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static void
ubser_cfg_set_break(struct ucom_softc *ucom, uint8_t onoff)
{
	struct ubser_softc *sc = ucom->sc_parent;
	uint8_t x = ucom->sc_portno;
	struct usb_device_request req;
	usb_error_t err;

	if (onoff) {

		req.bmRequestType = UT_READ_VENDOR_INTERFACE;
		req.bRequest = VENDOR_SET_BREAK;
		req.wValue[0] = x;
		req.wValue[1] = 0;
		req.wIndex[0] = sc->sc_iface_no;
		req.wIndex[1] = 0;
		USETW(req.wLength, 0);

		err = ucom_cfg_do_request(sc->sc_udev, ucom, 
		    &req, NULL, 0, 1000);
		if (err) {
			DPRINTFN(0, "send break failed, error=%s\n",
			    usbd_errstr(err));
		}
	}
}