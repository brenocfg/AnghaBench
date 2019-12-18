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
struct ufoma_softc {scalar_t__ sc_currentmode; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_udev; scalar_t__ sc_ctrl_iface_no; int /*<<< orphan*/  sc_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCDC_SET_CONTROL_LINE_STATE ; 
 scalar_t__ UMCPC_ACM_MODE_OBEX ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  ucom_cfg_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ufoma_cfg_set_line_state(struct ufoma_softc *sc)
{
	struct usb_device_request req;

	/* Don't send line state emulation request for OBEX port */
	if (sc->sc_currentmode == UMCPC_ACM_MODE_OBEX) {
		return;
	}
	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = UCDC_SET_CONTROL_LINE_STATE;
	USETW(req.wValue, sc->sc_line);
	req.wIndex[0] = sc->sc_ctrl_iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, 0);

	ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom, 
	    &req, NULL, 0, 1000);
}