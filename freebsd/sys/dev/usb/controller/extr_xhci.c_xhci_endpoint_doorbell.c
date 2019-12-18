#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct xhci_softc {int dummy; } ;
struct TYPE_8__ {scalar_t__ control_xfr; } ;
struct usb_xfer {int endpointno; int /*<<< orphan*/  stream_id; TYPE_3__* xroot; TYPE_4__ flags_int; } ;
struct TYPE_7__ {TYPE_2__* udev; int /*<<< orphan*/  bus; } ;
struct TYPE_5__ {scalar_t__ self_suspended; } ;
struct TYPE_6__ {int controller_slot_id; TYPE_1__ flags; } ;

/* Variables and functions */
 int UE_DIR_IN ; 
 struct xhci_softc* XHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int XHCI_DB_SID_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_DOORBELL (int) ; 
 int XHCI_EPNO2EPID (int) ; 
 int /*<<< orphan*/  XWRITE4 (struct xhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  door ; 

__attribute__((used)) static void
xhci_endpoint_doorbell(struct usb_xfer *xfer)
{
	struct xhci_softc *sc = XHCI_BUS2SC(xfer->xroot->bus);
	uint8_t epno;
	uint8_t index;

	epno = xfer->endpointno;
	if (xfer->flags_int.control_xfr)
		epno |= UE_DIR_IN;

	epno = XHCI_EPNO2EPID(epno);
	index = xfer->xroot->udev->controller_slot_id;

	if (xfer->xroot->udev->flags.self_suspended == 0) {
		XWRITE4(sc, door, XHCI_DOORBELL(index),
		    epno | XHCI_DB_SID_SET(xfer->stream_id));
	}
}