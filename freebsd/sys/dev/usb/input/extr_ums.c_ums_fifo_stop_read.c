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
struct ums_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ums_stop_rx (struct ums_softc*) ; 
 struct ums_softc* usb_fifo_softc (struct usb_fifo*) ; 

__attribute__((used)) static void
ums_fifo_stop_read(struct usb_fifo *fifo)
{
	struct ums_softc *sc = usb_fifo_softc(fifo);

	ums_stop_rx(sc);
}