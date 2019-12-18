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
struct uep_softc {int /*<<< orphan*/ * xfer; } ;

/* Variables and functions */
 size_t UEP_INTR_DT ; 
 struct uep_softc* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uep_stop_read(struct usb_fifo *fifo)
{
	struct uep_softc *sc = usb_fifo_softc(fifo);

	usbd_transfer_stop(sc->xfer[UEP_INTR_DT]);
}