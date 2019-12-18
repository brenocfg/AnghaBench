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
struct usb_device_request {int /*<<< orphan*/  bmRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; } ;
struct ulpt_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_iface_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  UR_SOFT_RESET ; 
 int USB_MS_HZ ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_OTHER ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usbd_do_request_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ulpt_reset(struct ulpt_softc *sc)
{
	struct usb_device_request req;

	DPRINTFN(2, "\n");

	req.bRequest = UR_SOFT_RESET;
	USETW(req.wValue, 0);
	USETW(req.wIndex, sc->sc_iface_no);
	USETW(req.wLength, 0);

	/*
	 * There was a mistake in the USB printer 1.0 spec that gave the
	 * request type as UT_WRITE_CLASS_OTHER; it should have been
	 * UT_WRITE_CLASS_INTERFACE.  Many printers use the old one,
	 * so we try both.
	 */

	mtx_lock(&sc->sc_mtx);
	req.bmRequestType = UT_WRITE_CLASS_OTHER;
	if (usbd_do_request_flags(sc->sc_udev, &sc->sc_mtx,
	    &req, NULL, 0, NULL, 2 * USB_MS_HZ)) {	/* 1.0 */
		req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
		if (usbd_do_request_flags(sc->sc_udev, &sc->sc_mtx,
		    &req, NULL, 0, NULL, 2 * USB_MS_HZ)) {	/* 1.1 */
			/* ignore error */
		}
	}
	mtx_unlock(&sc->sc_mtx);
}