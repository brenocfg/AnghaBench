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
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct ucom_softc {size_t sc_subunit; struct u3g_softc* sc_parent; } ;
struct u3g_softc {int /*<<< orphan*/  sc_udev; scalar_t__* sc_iface; int /*<<< orphan*/ * sc_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCDC_SET_CONTROL_LINE_STATE ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  ucom_cfg_do_request (int /*<<< orphan*/ ,struct ucom_softc*,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
u3g_cfg_set_line(struct ucom_softc *ucom)
{
	struct u3g_softc *sc = ucom->sc_parent;
	struct usb_device_request req;

	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = UCDC_SET_CONTROL_LINE_STATE;
	USETW(req.wValue, sc->sc_line[ucom->sc_subunit]);
	req.wIndex[0] = sc->sc_iface[ucom->sc_subunit];
	req.wIndex[1] = 0;
	USETW(req.wLength, 0);

	ucom_cfg_do_request(sc->sc_udev, ucom,
	    &req, NULL, 0, 1000);
}