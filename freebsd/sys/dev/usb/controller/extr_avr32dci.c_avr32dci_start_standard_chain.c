#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct usb_xfer {int endpointno; scalar_t__ timeout; TYPE_1__* xroot; } ;
struct avr32dci_softc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  intr_q; } ;
struct TYPE_3__ {TYPE_2__* bus; } ;

/* Variables and functions */
 struct avr32dci_softc* AVR32_BUS2SC (TYPE_2__*) ; 
 int /*<<< orphan*/  AVR32_INT_EPT_INT (int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int UE_ADDR ; 
 int /*<<< orphan*/  avr32dci_mod_ien (struct avr32dci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avr32dci_timeout ; 
 scalar_t__ avr32dci_xfer_do_fifo (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_enqueue (int /*<<< orphan*/ *,struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_timeout_ms (struct usb_xfer*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
avr32dci_start_standard_chain(struct usb_xfer *xfer)
{
	DPRINTFN(9, "\n");

	/* poll one time - will turn on interrupts */
	if (avr32dci_xfer_do_fifo(xfer)) {
		uint8_t ep_no = xfer->endpointno & UE_ADDR;
		struct avr32dci_softc *sc = AVR32_BUS2SC(xfer->xroot->bus);

		avr32dci_mod_ien(sc, AVR32_INT_EPT_INT(ep_no), 0);

		/* put transfer on interrupt queue */
		usbd_transfer_enqueue(&xfer->xroot->bus->intr_q, xfer);

		/* start timeout, if any */
		if (xfer->timeout != 0) {
			usbd_transfer_timeout_ms(xfer,
			    &avr32dci_timeout, xfer->timeout);
		}
	}
}