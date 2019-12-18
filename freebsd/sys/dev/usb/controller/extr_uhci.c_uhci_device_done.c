#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
struct TYPE_15__ {int /*<<< orphan*/ * sc_intr_p_last; int /*<<< orphan*/  sc_fs_ctl_p_last; int /*<<< orphan*/  sc_ls_ctl_p_last; int /*<<< orphan*/  sc_bulk_p_last; int /*<<< orphan*/  sc_bus; } ;
typedef  TYPE_4__ uhci_softc_t ;
struct TYPE_16__ {int /*<<< orphan*/  page_cache; } ;
typedef  TYPE_5__ uhci_qh_t ;
struct TYPE_12__ {size_t curr_dma_set; scalar_t__ bandwidth_reclaimed; } ;
struct usb_xfer {size_t qh_pos; int /*<<< orphan*/ * td_transfer_last; int /*<<< orphan*/ * td_transfer_first; TYPE_3__* xroot; TYPE_1__ flags_int; TYPE_5__** qh_start; TYPE_10__* endpoint; } ;
struct usb_pipe_methods {int dummy; } ;
struct TYPE_14__ {TYPE_2__* udev; int /*<<< orphan*/  bus; } ;
struct TYPE_13__ {scalar_t__ speed; } ;
struct TYPE_11__ {struct usb_pipe_methods* methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_xfer*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 TYPE_4__* UHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UHCI_REMOVE_QH (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ USB_SPEED_LOW ; 
 struct usb_pipe_methods const uhci_device_bulk_methods ; 
 struct usb_pipe_methods const uhci_device_ctrl_methods ; 
 struct usb_pipe_methods const uhci_device_intr_methods ; 
 struct usb_pipe_methods const uhci_device_isoc_methods ; 
 int /*<<< orphan*/  uhci_isoc_done (TYPE_4__*,struct usb_xfer*) ; 
 int /*<<< orphan*/  uhci_rem_loop (TYPE_4__*) ; 
 int /*<<< orphan*/  usb_pc_cpu_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhci_device_done(struct usb_xfer *xfer, usb_error_t error)
{
	const struct usb_pipe_methods *methods = xfer->endpoint->methods;
	uhci_softc_t *sc = UHCI_BUS2SC(xfer->xroot->bus);
	uhci_qh_t *qh;

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

	DPRINTFN(2, "xfer=%p, endpoint=%p, error=%d\n",
	    xfer, xfer->endpoint, error);

	qh = xfer->qh_start[xfer->flags_int.curr_dma_set];
	if (qh) {
		usb_pc_cpu_invalidate(qh->page_cache);
	}
	if (xfer->flags_int.bandwidth_reclaimed) {
		xfer->flags_int.bandwidth_reclaimed = 0;
		uhci_rem_loop(sc);
	}
	if (methods == &uhci_device_bulk_methods) {
		UHCI_REMOVE_QH(qh, sc->sc_bulk_p_last);
	}
	if (methods == &uhci_device_ctrl_methods) {
		if (xfer->xroot->udev->speed == USB_SPEED_LOW) {
			UHCI_REMOVE_QH(qh, sc->sc_ls_ctl_p_last);
		} else {
			UHCI_REMOVE_QH(qh, sc->sc_fs_ctl_p_last);
		}
	}
	if (methods == &uhci_device_intr_methods) {
		UHCI_REMOVE_QH(qh, sc->sc_intr_p_last[xfer->qh_pos]);
	}
	/*
	 * Only finish isochronous transfers once
	 * which will update "xfer->frlengths".
	 */
	if (xfer->td_transfer_first &&
	    xfer->td_transfer_last) {
		if (methods == &uhci_device_isoc_methods) {
			uhci_isoc_done(sc, xfer);
		}
		xfer->td_transfer_first = NULL;
		xfer->td_transfer_last = NULL;
	}
	/* dequeue transfer and start next transfer */
	usbd_transfer_done(xfer, error);
}