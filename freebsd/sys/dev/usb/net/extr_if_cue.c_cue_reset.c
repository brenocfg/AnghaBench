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
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct cue_softc {int /*<<< orphan*/  sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUE_CMD_RESET ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_VENDOR_DEVICE ; 
 int hz ; 
 scalar_t__ uether_do_request (int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uether_pause (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
cue_reset(struct cue_softc *sc)
{
	struct usb_device_request req;

	req.bmRequestType = UT_WRITE_VENDOR_DEVICE;
	req.bRequest = CUE_CMD_RESET;
	USETW(req.wValue, 0);
	USETW(req.wIndex, 0);
	USETW(req.wLength, 0);

	if (uether_do_request(&sc->sc_ue, &req, NULL, 1000)) {
		/* ignore any errors */
	}

	/*
	 * wait a little while for the chip to get its brains in order:
	 */
	uether_pause(&sc->sc_ue, hz / 100);
}