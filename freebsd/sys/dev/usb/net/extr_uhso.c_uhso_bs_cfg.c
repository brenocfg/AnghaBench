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
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct uhso_softc {int /*<<< orphan*/  sc_line; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_ucom; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_iface_no; int /*<<< orphan*/  sc_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCDC_SET_CONTROL_LINE_STATE ; 
 int UHSO_IFACE_USB_TYPE (int /*<<< orphan*/ ) ; 
 int UHSO_IF_BULK ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ucom_cfg_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static void
uhso_bs_cfg(struct uhso_softc *sc)
{
	struct usb_device_request req;
	usb_error_t uerr;

	if (!(UHSO_IFACE_USB_TYPE(sc->sc_type) & UHSO_IF_BULK))
		return;

	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = UCDC_SET_CONTROL_LINE_STATE;
	USETW(req.wValue, sc->sc_line);
	USETW(req.wIndex, sc->sc_iface_no);
	USETW(req.wLength, 0);

	uerr = ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom[0], &req, NULL, 0, 1000);
	if (uerr != 0) {
		device_printf(sc->sc_dev, "failed to set ctrl line state to "
		    "0x%02x: %s\n", sc->sc_line, usbd_errstr(uerr));
	}
}