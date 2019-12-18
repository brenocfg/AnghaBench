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
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct uslcom_softc {int sc_iface_no; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_udev; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; void* bmRequestType; } ;
struct ucom_softc {struct uslcom_softc* sc_parent; } ;
struct termios {int c_cflag; scalar_t__ c_ospeed; } ;
typedef  int /*<<< orphan*/  flowctrl ;
typedef  int /*<<< orphan*/  baudrate ;

/* Variables and functions */
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int USLCOM_FLOW_CTS_HS ; 
 int USLCOM_FLOW_DTR_ON ; 
 int USLCOM_FLOW_RTS_HS ; 
 int USLCOM_FLOW_RTS_ON ; 
 int USLCOM_PARITY_EVEN ; 
 int USLCOM_PARITY_NONE ; 
 int USLCOM_PARITY_ODD ; 
 int /*<<< orphan*/  USLCOM_SET_BAUDRATE ; 
 int USLCOM_SET_DATA_BITS (int) ; 
 int /*<<< orphan*/  USLCOM_SET_FLOW ; 
 int /*<<< orphan*/  USLCOM_SET_LINE_CTL ; 
 int USLCOM_STOP_BITS_1 ; 
 int USLCOM_STOP_BITS_2 ; 
 void* USLCOM_WRITE ; 
 scalar_t__ htole32 (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ ucom_cfg_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uslcom_cfg_param(struct ucom_softc *ucom, struct termios *t)
{
	struct uslcom_softc *sc = ucom->sc_parent;
	struct usb_device_request req;
	uint32_t baudrate, flowctrl[4];
	uint16_t data;

	DPRINTF("\n");

	baudrate = t->c_ospeed;
	req.bmRequestType = USLCOM_WRITE;
	req.bRequest = USLCOM_SET_BAUDRATE;
	USETW(req.wValue, 0);
	USETW(req.wIndex, sc->sc_iface_no);
	USETW(req.wLength, sizeof(baudrate));

	if (ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom,
	    &req, &baudrate, 0, 1000)) {
		printf("Set baudrate failed (ignored)\n");
	}

	if (t->c_cflag & CSTOPB)
		data = USLCOM_STOP_BITS_2;
	else
		data = USLCOM_STOP_BITS_1;
	if (t->c_cflag & PARENB) {
		if (t->c_cflag & PARODD)
			data |= USLCOM_PARITY_ODD;
		else
			data |= USLCOM_PARITY_EVEN;
	} else
		data |= USLCOM_PARITY_NONE;
	switch (t->c_cflag & CSIZE) {
	case CS5:
		data |= USLCOM_SET_DATA_BITS(5);
		break;
	case CS6:
		data |= USLCOM_SET_DATA_BITS(6);
		break;
	case CS7:
		data |= USLCOM_SET_DATA_BITS(7);
		break;
	case CS8:
		data |= USLCOM_SET_DATA_BITS(8);
		break;
	}

	req.bmRequestType = USLCOM_WRITE;
	req.bRequest = USLCOM_SET_LINE_CTL;
	USETW(req.wValue, data);
	USETW(req.wIndex, sc->sc_iface_no);
	USETW(req.wLength, 0);

	if (ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom,
	    &req, NULL, 0, 1000)) {
		DPRINTF("Set format failed (ignored)\n");
	}

	if (t->c_cflag & CRTSCTS) {
		flowctrl[0] = htole32(USLCOM_FLOW_DTR_ON | USLCOM_FLOW_CTS_HS);
		flowctrl[1] = htole32(USLCOM_FLOW_RTS_HS);
	} else {
		flowctrl[0] = htole32(USLCOM_FLOW_DTR_ON);
		flowctrl[1] = htole32(USLCOM_FLOW_RTS_ON);
	}
	flowctrl[2] = 0;
	flowctrl[3] = 0;
	req.bmRequestType = USLCOM_WRITE;
	req.bRequest = USLCOM_SET_FLOW;
	USETW(req.wValue, 0);
	USETW(req.wIndex, sc->sc_iface_no);
	USETW(req.wLength, sizeof(flowctrl));

	if (ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom,
	    &req, flowctrl, 0, 1000)) {
		DPRINTF("Set flowcontrol failed (ignored)\n");
	}
}