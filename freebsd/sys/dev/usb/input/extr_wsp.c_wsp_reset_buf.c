#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * fp; } ;
struct wsp_softc {TYPE_1__ sc_fifo; } ;

/* Variables and functions */
 size_t USB_FIFO_RX ; 
 int /*<<< orphan*/  usb_fifo_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wsp_reset_buf(struct wsp_softc *sc)
{
	/* reset read queue */
	usb_fifo_reset(sc->sc_fifo.fp[USB_FIFO_RX]);
}