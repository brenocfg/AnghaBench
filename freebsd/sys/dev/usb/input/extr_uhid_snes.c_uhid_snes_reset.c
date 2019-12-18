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
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; } ;
struct uhid_snes_softc {int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_usb_device; int /*<<< orphan*/  sc_iface_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  UREQ_SOFT_RESET ; 
 int USB_MS_HZ ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int usbd_do_request_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
uhid_snes_reset(struct uhid_snes_softc *sc)
{
	struct usb_device_request req;
	int error;

	req.bRequest = UREQ_SOFT_RESET;
	USETW(req.wValue, 0);
	USETW(req.wIndex, sc->sc_iface_num);
	USETW(req.wLength, 0);

	mtx_lock(&sc->sc_mutex);

	error = usbd_do_request_flags(sc->sc_usb_device, &sc->sc_mutex,
	    &req, NULL, 0, NULL, 2 * USB_MS_HZ);

	if (error) {
		usbd_do_request_flags(sc->sc_usb_device, &sc->sc_mutex,
		    &req, NULL, 0, NULL, 2 * USB_MS_HZ);
	}

	mtx_unlock(&sc->sc_mutex);
}