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
typedef  int /*<<< orphan*/  uint8_t ;
struct usie_softc {int sc_if_ifnum; } ;
struct usie_hip {scalar_t__ param; int /*<<< orphan*/  id; scalar_t__ len; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCDC_SEND_ENCAPSULATED_COMMAND ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int usie_do_request (struct usie_softc*,struct usb_device_request*,struct usie_hip*) ; 

__attribute__((used)) static int
usie_if_cmd(struct usie_softc *sc, uint8_t cmd)
{
	struct usb_device_request req;
	struct usie_hip msg;

	msg.len = 0;
	msg.id = cmd;
	msg.param = 0;

	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = UCDC_SEND_ENCAPSULATED_COMMAND;
	USETW(req.wValue, 0);
	USETW(req.wIndex, sc->sc_if_ifnum);
	USETW(req.wLength, sizeof(msg));

	DPRINTF("cmd=%x\n", cmd);

	return (usie_do_request(sc, &req, &msg));
}