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
struct usie_softc {int /*<<< orphan*/ * sc_uc_ifnum; int /*<<< orphan*/ *** sc_uc_xfer; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct ucom_softc {size_t sc_subunit; struct usie_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USIE_LINK_STATE ; 
 size_t USIE_UC_STATUS ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 int /*<<< orphan*/  usie_do_request (struct usie_softc*,struct usb_device_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usie_uc_update_line_state(struct ucom_softc *ucom, uint8_t ls)
{
	struct usie_softc *sc = ucom->sc_parent;
	struct usb_device_request req;

	if (sc->sc_uc_xfer[ucom->sc_subunit][USIE_UC_STATUS] == NULL)
		return;

	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = USIE_LINK_STATE;
	USETW(req.wValue, ls);
	USETW(req.wIndex, sc->sc_uc_ifnum[ucom->sc_subunit]);
	USETW(req.wLength, 0);

	DPRINTF("sc_uc_ifnum=%d\n", sc->sc_uc_ifnum[ucom->sc_subunit]);

	usie_do_request(sc, &req, NULL);
}