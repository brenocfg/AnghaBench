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
struct usb_cdc_line_state {int bDataBits; int /*<<< orphan*/  bParityType; int /*<<< orphan*/  bCharFormat; int /*<<< orphan*/  dwDTERate; } ;
struct ufoma_softc {scalar_t__ sc_currentmode; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_udev; scalar_t__ sc_ctrl_iface_no; scalar_t__ sc_nobulk; } ;
struct ucom_softc {struct ufoma_softc* sc_parent; } ;
struct termios {int c_cflag; int /*<<< orphan*/  c_ospeed; } ;
typedef  int /*<<< orphan*/  ls ;

/* Variables and functions */
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  UCDC_LINE_STATE_LENGTH ; 
 int /*<<< orphan*/  UCDC_PARITY_EVEN ; 
 int /*<<< orphan*/  UCDC_PARITY_NONE ; 
 int /*<<< orphan*/  UCDC_PARITY_ODD ; 
 int /*<<< orphan*/  UCDC_SET_LINE_CODING ; 
 int /*<<< orphan*/  UCDC_STOP_BIT_1 ; 
 int /*<<< orphan*/  UCDC_STOP_BIT_2 ; 
 scalar_t__ UMCPC_ACM_MODE_OBEX ; 
 int /*<<< orphan*/  USETDW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  memset (struct usb_cdc_line_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ucom_cfg_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,struct usb_cdc_line_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ufoma_cfg_param(struct ucom_softc *ucom, struct termios *t)
{
	struct ufoma_softc *sc = ucom->sc_parent;
	struct usb_device_request req;
	struct usb_cdc_line_state ls;

	if (sc->sc_nobulk ||
	    (sc->sc_currentmode == UMCPC_ACM_MODE_OBEX)) {
		return;
	}
	DPRINTF("\n");

	memset(&ls, 0, sizeof(ls));

	USETDW(ls.dwDTERate, t->c_ospeed);

	if (t->c_cflag & CSTOPB) {
		ls.bCharFormat = UCDC_STOP_BIT_2;
	} else {
		ls.bCharFormat = UCDC_STOP_BIT_1;
	}

	if (t->c_cflag & PARENB) {
		if (t->c_cflag & PARODD) {
			ls.bParityType = UCDC_PARITY_ODD;
		} else {
			ls.bParityType = UCDC_PARITY_EVEN;
		}
	} else {
		ls.bParityType = UCDC_PARITY_NONE;
	}

	switch (t->c_cflag & CSIZE) {
	case CS5:
		ls.bDataBits = 5;
		break;
	case CS6:
		ls.bDataBits = 6;
		break;
	case CS7:
		ls.bDataBits = 7;
		break;
	case CS8:
		ls.bDataBits = 8;
		break;
	}

	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = UCDC_SET_LINE_CODING;
	USETW(req.wValue, 0);
	req.wIndex[0] = sc->sc_ctrl_iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, UCDC_LINE_STATE_LENGTH);

	ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom, 
	    &req, &ls, 0, 1000);
}