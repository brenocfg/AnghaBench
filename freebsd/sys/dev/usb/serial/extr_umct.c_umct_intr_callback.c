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
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int dummy; } ;
struct umct_softc {scalar_t__ sc_swap_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  umct_intr_callback_sub (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umct_read_callback_sub (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 struct umct_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
umct_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct umct_softc *sc = usbd_xfer_softc(xfer);

	if (sc->sc_swap_cb)
		umct_read_callback_sub(xfer, error);
	else
		umct_intr_callback_sub(xfer, error);
}