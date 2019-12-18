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
typedef  int /*<<< orphan*/  uint8_t ;
struct uvisor_softc {int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_udev; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct ucom_softc {struct uvisor_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_VENDOR_ENDPOINT ; 
 int /*<<< orphan*/  UVISOR_CLOSE_NOTIFICATION ; 
 int UVISOR_CONNECTION_INFO_SIZE ; 
 scalar_t__ ucom_cfg_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static void
uvisor_cfg_close(struct ucom_softc *ucom)
{
	struct uvisor_softc *sc = ucom->sc_parent;
	uint8_t buffer[UVISOR_CONNECTION_INFO_SIZE];
	struct usb_device_request req;
	usb_error_t err;

	req.bmRequestType = UT_READ_VENDOR_ENDPOINT;	/* XXX read? */
	req.bRequest = UVISOR_CLOSE_NOTIFICATION;
	USETW(req.wValue, 0);
	USETW(req.wIndex, 0);
	USETW(req.wLength, UVISOR_CONNECTION_INFO_SIZE);

	err = ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom, 
	    &req, buffer, 0, 1000);
	if (err) {
		DPRINTFN(0, "close notification failed, error=%s\n",
		    usbd_errstr(err));
	}
}