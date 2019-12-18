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
struct run_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  RUN_DEBUG_USB ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_LOCK_ASSERT (struct run_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_delay (struct run_softc*,int) ; 
 scalar_t__ usbd_do_request_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static usb_error_t
run_do_request(struct run_softc *sc,
    struct usb_device_request *req, void *data)
{
	usb_error_t err;
	int ntries = 10;

	RUN_LOCK_ASSERT(sc, MA_OWNED);

	while (ntries--) {
		err = usbd_do_request_flags(sc->sc_udev, &sc->sc_mtx,
		    req, data, 0, NULL, 250 /* ms */);
		if (err == 0)
			break;
		RUN_DPRINTF(sc, RUN_DEBUG_USB,
		    "Control request failed, %s (retrying)\n",
		    usbd_errstr(err));
		run_delay(sc, 10);
	}
	return (err);
}