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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct ufoma_softc {scalar_t__ sc_currentmode; int sc_acm_cap; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_udev; scalar_t__ sc_ctrl_iface_no; scalar_t__ sc_nobulk; } ;
struct ucom_softc {struct ufoma_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCDC_BREAK_OFF ; 
 int /*<<< orphan*/  UCDC_BREAK_ON ; 
 int /*<<< orphan*/  UCDC_SEND_BREAK ; 
 scalar_t__ UMCPC_ACM_MODE_OBEX ; 
 int USB_CDC_ACM_HAS_BREAK ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  ucom_cfg_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ufoma_cfg_set_break(struct ucom_softc *ucom, uint8_t onoff)
{
	struct ufoma_softc *sc = ucom->sc_parent;
	struct usb_device_request req;
	uint16_t wValue;

	if (sc->sc_nobulk ||
	    (sc->sc_currentmode == UMCPC_ACM_MODE_OBEX)) {
		return;
	}
	if (!(sc->sc_acm_cap & USB_CDC_ACM_HAS_BREAK)) {
		return;
	}
	wValue = onoff ? UCDC_BREAK_ON : UCDC_BREAK_OFF;

	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = UCDC_SEND_BREAK;
	USETW(req.wValue, wValue);
	req.wIndex[0] = sc->sc_ctrl_iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, 0);

	ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom, 
	    &req, NULL, 0, 1000);
}