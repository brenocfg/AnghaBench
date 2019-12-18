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
struct usb_fifo {int dummy; } ;
struct atp_softc {int sc_pollrate; int /*<<< orphan*/ ** sc_xfer; } ;

/* Variables and functions */
 size_t ATP_INTR_DT ; 
 struct atp_softc* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_xfer_set_interval (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
atp_start_read(struct usb_fifo *fifo)
{
	struct atp_softc *sc = usb_fifo_softc(fifo);
	int rate;

	/* Check if we should override the default polling interval */
	rate = sc->sc_pollrate;
	/* Range check rate */
	if (rate > 1000)
		rate = 1000;
	/* Check for set rate */
	if ((rate > 0) && (sc->sc_xfer[ATP_INTR_DT] != NULL)) {
		/* Stop current transfer, if any */
		usbd_transfer_stop(sc->sc_xfer[ATP_INTR_DT]);
		/* Set new interval */
		usbd_xfer_set_interval(sc->sc_xfer[ATP_INTR_DT], 1000 / rate);
		/* Only set pollrate once */
		sc->sc_pollrate = 0;
	}

	usbd_transfer_start(sc->sc_xfer[ATP_INTR_DT]);
}