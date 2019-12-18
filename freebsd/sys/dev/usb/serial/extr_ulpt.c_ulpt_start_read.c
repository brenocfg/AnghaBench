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
struct ulpt_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 size_t ULPT_BULK_DT_RD ; 
 struct ulpt_softc* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ulpt_start_read(struct usb_fifo *fifo)
{
	struct ulpt_softc *sc = usb_fifo_softc(fifo);

	usbd_transfer_start(sc->sc_xfer[ULPT_BULK_DT_RD]);
}