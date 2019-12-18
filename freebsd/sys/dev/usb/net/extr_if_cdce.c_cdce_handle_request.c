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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device_request {scalar_t__ bmRequestType; scalar_t__ bRequest; } ;
struct cdce_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_notify_state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t CDCE_INTR_TX ; 
 int /*<<< orphan*/  CDCE_NOTIFY_SPEED_CHANGE ; 
 int ENXIO ; 
 scalar_t__ UCDC_NCM_SET_ETHERNET_PACKET_FILTER ; 
 scalar_t__ UT_WRITE_CLASS_INTERFACE ; 
 struct cdce_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdce_handle_request(device_t dev,
    const void *preq, void **pptr, uint16_t *plen,
    uint16_t offset, uint8_t *pstate)
{
	struct cdce_softc *sc = device_get_softc(dev);
	const struct usb_device_request *req = preq;
	uint8_t is_complete = *pstate;

	/*
	 * When Mac OS X resumes after suspending it expects
	 * to be notified again after this request.
	 */
	if (req->bmRequestType == UT_WRITE_CLASS_INTERFACE && \
	    req->bRequest == UCDC_NCM_SET_ETHERNET_PACKET_FILTER) {

		if (is_complete == 1) {
			mtx_lock(&sc->sc_mtx);
			sc->sc_notify_state = CDCE_NOTIFY_SPEED_CHANGE;
			usbd_transfer_start(sc->sc_xfer[CDCE_INTR_TX]);
			mtx_unlock(&sc->sc_mtx);
		}

		return (0);
	}

	return (ENXIO);			/* use builtin handler */
}