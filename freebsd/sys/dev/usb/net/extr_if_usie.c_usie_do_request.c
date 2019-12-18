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
struct usie_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; } ;
struct usb_device_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_MS_TO_TICKS (int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usbd_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,void*) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 

__attribute__((used)) static int
usie_do_request(struct usie_softc *sc, struct usb_device_request *req,
    void *data)
{
	int err = 0;
	int ntries;

	mtx_assert(&sc->sc_mtx, MA_OWNED);

	for (ntries = 0; ntries != 10; ntries++) {
		err = usbd_do_request(sc->sc_udev,
		    &sc->sc_mtx, req, data);
		if (err == 0)
			break;

		DPRINTF("Control request failed: %s %d/10\n",
		    usbd_errstr(err), ntries);

		usb_pause_mtx(&sc->sc_mtx, USB_MS_TO_TICKS(10));
	}
	return (err);
}