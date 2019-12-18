#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
struct TYPE_9__ {size_t curr_dma_set; } ;
struct usb_xfer {size_t qh_pos; int /*<<< orphan*/ * td_transfer_last; int /*<<< orphan*/ * td_transfer_first; TYPE_2__ flags_int; TYPE_4__** qh_start; TYPE_7__* endpoint; TYPE_1__* xroot; } ;
struct usb_pipe_methods {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  sc_isoc_p_last; int /*<<< orphan*/ * sc_intr_p_last; int /*<<< orphan*/  sc_ctrl_p_last; int /*<<< orphan*/  sc_bulk_p_last; int /*<<< orphan*/  sc_bus; } ;
typedef  TYPE_3__ ohci_softc_t ;
struct TYPE_11__ {int /*<<< orphan*/  page_cache; } ;
typedef  TYPE_4__ ohci_ed_t ;
struct TYPE_12__ {struct usb_pipe_methods* methods; } ;
struct TYPE_8__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_xfer*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 TYPE_3__* OHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OHCI_REMOVE_QH (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_pipe_methods const ohci_device_bulk_methods ; 
 struct usb_pipe_methods const ohci_device_ctrl_methods ; 
 struct usb_pipe_methods const ohci_device_intr_methods ; 
 struct usb_pipe_methods const ohci_device_isoc_methods ; 
 int /*<<< orphan*/  usb_pc_cpu_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ohci_device_done(struct usb_xfer *xfer, usb_error_t error)
{
	const struct usb_pipe_methods *methods = xfer->endpoint->methods;
	ohci_softc_t *sc = OHCI_BUS2SC(xfer->xroot->bus);
	ohci_ed_t *ed;

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);


	DPRINTFN(2, "xfer=%p, endpoint=%p, error=%d\n",
	    xfer, xfer->endpoint, error);

	ed = xfer->qh_start[xfer->flags_int.curr_dma_set];
	if (ed) {
		usb_pc_cpu_invalidate(ed->page_cache);
	}
	if (methods == &ohci_device_bulk_methods) {
		OHCI_REMOVE_QH(ed, sc->sc_bulk_p_last);
	}
	if (methods == &ohci_device_ctrl_methods) {
		OHCI_REMOVE_QH(ed, sc->sc_ctrl_p_last);
	}
	if (methods == &ohci_device_intr_methods) {
		OHCI_REMOVE_QH(ed, sc->sc_intr_p_last[xfer->qh_pos]);
	}
	if (methods == &ohci_device_isoc_methods) {
		OHCI_REMOVE_QH(ed, sc->sc_isoc_p_last);
	}
	xfer->td_transfer_first = NULL;
	xfer->td_transfer_last = NULL;

	/* dequeue transfer and start next transfer */
	usbd_transfer_done(xfer, error);
}