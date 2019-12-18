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
struct ulpt_softc {scalar_t__ sc_fflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ulpt_reset (struct ulpt_softc*) ; 
 int unlpt_open (struct usb_fifo*,int) ; 
 struct ulpt_softc* usb_fifo_softc (struct usb_fifo*) ; 

__attribute__((used)) static int
ulpt_open(struct usb_fifo *fifo, int fflags)
{
	struct ulpt_softc *sc = usb_fifo_softc(fifo);

	/* we assume that open is a serial process */

	if (sc->sc_fflags == 0) {

		/* reset USB parallel port */

		ulpt_reset(sc);
	}
	return (unlpt_open(fifo, fflags));
}