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
struct urio_softc {int /*<<< orphan*/  sc_flags; struct usb_xfer** sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  URIO_FLAG_WRITE_STALL ; 
 size_t URIO_T_WR ; 
 scalar_t__ usbd_clear_stall_callback (struct usb_xfer*,struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_start (struct usb_xfer*) ; 
 struct urio_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
urio_write_clear_stall_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct urio_softc *sc = usbd_xfer_softc(xfer);
	struct usb_xfer *xfer_other = sc->sc_xfer[URIO_T_WR];

	if (usbd_clear_stall_callback(xfer, xfer_other)) {
		DPRINTF("stall cleared\n");
		sc->sc_flags &= ~URIO_FLAG_WRITE_STALL;
		usbd_transfer_start(xfer_other);
	}
}