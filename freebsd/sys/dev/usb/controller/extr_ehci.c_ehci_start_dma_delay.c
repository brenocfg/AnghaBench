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
struct usb_xfer {TYPE_1__* xroot; } ;
struct ehci_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 struct ehci_softc* EHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_doorbell_async (struct ehci_softc*) ; 
 int /*<<< orphan*/  ehci_start_dma_delay_second ; 
 int /*<<< orphan*/  usbd_transfer_timeout_ms (struct usb_xfer*,void (*) (void*),int) ; 

__attribute__((used)) static void
ehci_start_dma_delay(struct usb_xfer *xfer)
{
	struct ehci_softc *sc = EHCI_BUS2SC(xfer->xroot->bus);

	DPRINTF("\n");

	/* trigger doorbell */
	ehci_doorbell_async(sc);

	/* give the doorbell 4ms */
	usbd_transfer_timeout_ms(xfer,
	    (void (*)(void *))&ehci_start_dma_delay_second, 4);
}