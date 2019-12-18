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
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {struct musbotg_td* td_transfer_cache; TYPE_1__* xroot; int /*<<< orphan*/  endpoint; } ;
struct musbotg_td {int channel; } ;
struct musbotg_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct musbotg_softc* MUSBOTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musbotg_channel_free (struct musbotg_softc*,struct musbotg_td*) ; 
 int /*<<< orphan*/  usbd_transfer_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
musbotg_device_done(struct usb_xfer *xfer, usb_error_t error)
{
	struct musbotg_td *td;
	struct musbotg_softc *sc;

	USB_BUS_LOCK_ASSERT(xfer->xroot->bus, MA_OWNED);

	DPRINTFN(1, "xfer=%p, endpoint=%p, error=%d\n",
	    xfer, xfer->endpoint, error);

	DPRINTFN(14, "disabled interrupts on endpoint\n");

	sc = MUSBOTG_BUS2SC(xfer->xroot->bus);
	td = xfer->td_transfer_cache;

	if (td && (td->channel != -1))
		musbotg_channel_free(sc, td);

	/* dequeue transfer and start next transfer */
	usbd_transfer_done(xfer, error);
}