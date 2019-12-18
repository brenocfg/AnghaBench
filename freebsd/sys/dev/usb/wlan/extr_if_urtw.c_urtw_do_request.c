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
typedef  scalar_t__ usb_error_t ;
struct usb_device_request {int dummy; } ;
struct urtw_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct urtw_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  URTW_ASSERT_LOCKED (struct urtw_softc*) ; 
 int /*<<< orphan*/  URTW_DEBUG_INIT ; 
 int hz ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 
 scalar_t__ usbd_do_request_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static usb_error_t
urtw_do_request(struct urtw_softc *sc,
    struct usb_device_request *req, void *data)
{
	usb_error_t err;
	int ntries = 10;

	URTW_ASSERT_LOCKED(sc);

	while (ntries--) {
		err = usbd_do_request_flags(sc->sc_udev, &sc->sc_mtx,
		    req, data, 0, NULL, 250 /* ms */);
		if (err == 0)
			break;

		DPRINTF(sc, URTW_DEBUG_INIT,
		    "Control request failed, %s (retrying)\n",
		    usbd_errstr(err));
		usb_pause_mtx(&sc->sc_mtx, hz / 100);
	}
	return (err);
}