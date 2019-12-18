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
struct uhid_snes_softc {int sc_fflags; } ;

/* Variables and functions */
 int FREAD ; 
 int /*<<< orphan*/  usb_fifo_free_buffer (struct usb_fifo*) ; 
 struct uhid_snes_softc* usb_fifo_softc (struct usb_fifo*) ; 

__attribute__((used)) static void
uhid_snes_close(struct usb_fifo *fifo, int fflags)
{
	struct uhid_snes_softc *sc = usb_fifo_softc(fifo);

	sc->sc_fflags &= ~(fflags & FREAD);
	usb_fifo_free_buffer(fifo);
}