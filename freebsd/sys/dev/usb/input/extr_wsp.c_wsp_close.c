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
struct wsp_softc {int dummy; } ;
struct usb_fifo {int dummy; } ;

/* Variables and functions */
 int FREAD ; 
 int /*<<< orphan*/  usb_fifo_free_buffer (struct usb_fifo*) ; 
 struct wsp_softc* usb_fifo_softc (struct usb_fifo*) ; 
 int /*<<< orphan*/  wsp_disable (struct wsp_softc*) ; 

__attribute__((used)) static void
wsp_close(struct usb_fifo *fifo, int fflags)
{
	if (fflags & FREAD) {
		struct wsp_softc *sc = usb_fifo_softc(fifo);

		wsp_disable(sc);
		usb_fifo_free_buffer(fifo);
	}
}