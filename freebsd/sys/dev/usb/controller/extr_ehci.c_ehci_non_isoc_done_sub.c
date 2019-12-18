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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ short_frames_ok; } ;
struct usb_xfer {size_t aframes; size_t nframes; void* td_transfer_last; TYPE_3__* xroot; int /*<<< orphan*/  endpointno; int /*<<< orphan*/  address; TYPE_4__* td_transfer_cache; TYPE_1__ flags_int; int /*<<< orphan*/ * frlengths; } ;
typedef  int /*<<< orphan*/  ehci_softc_t ;
struct TYPE_8__ {scalar_t__ len; struct TYPE_8__* alt_next; struct TYPE_8__* obj_next; int /*<<< orphan*/  qtd_status; int /*<<< orphan*/  page_cache; } ;
typedef  TYPE_4__ ehci_qtd_t ;
struct TYPE_7__ {TYPE_2__* udev; int /*<<< orphan*/  bus; } ;
struct TYPE_6__ {scalar_t__ address; int /*<<< orphan*/ * parent_hs_hub; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * EHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int EHCI_QTD_ACTIVE ; 
 int EHCI_QTD_BABBLE ; 
 int EHCI_QTD_BUFERR ; 
 scalar_t__ EHCI_QTD_GET_BYTES (int) ; 
 scalar_t__ EHCI_QTD_GET_CERR (int) ; 
 int EHCI_QTD_HALTED ; 
 int EHCI_QTD_MISSEDMICRO ; 
 int EHCI_QTD_PINGSTATE ; 
 int EHCI_QTD_SPLITXSTATE ; 
 int EHCI_QTD_STATERRS ; 
 int EHCI_QTD_XACTERR ; 
 int /*<<< orphan*/  USB_ERR_IOERROR ; 
 int /*<<< orphan*/  USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  USB_ERR_STALLED ; 
 int /*<<< orphan*/  ehci_data_toggle_update (struct usb_xfer*,scalar_t__,scalar_t__) ; 
 int hc32toh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pc_cpu_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
ehci_non_isoc_done_sub(struct usb_xfer *xfer)
{
	ehci_softc_t *sc = EHCI_BUS2SC(xfer->xroot->bus);
	ehci_qtd_t *td;
	ehci_qtd_t *td_alt_next;
	uint32_t status;
	uint16_t len;

	td = xfer->td_transfer_cache;
	td_alt_next = td->alt_next;

	if (xfer->aframes != xfer->nframes) {
		usbd_xfer_set_frame_len(xfer, xfer->aframes, 0);
	}
	while (1) {

		usb_pc_cpu_invalidate(td->page_cache);
		status = hc32toh(sc, td->qtd_status);

		len = EHCI_QTD_GET_BYTES(status);

		/*
	         * Verify the status length and
		 * add the length to "frlengths[]":
	         */
		if (len > td->len) {
			/* should not happen */
			DPRINTF("Invalid status length, "
			    "0x%04x/0x%04x bytes\n", len, td->len);
			status |= EHCI_QTD_HALTED;
		} else if (xfer->aframes != xfer->nframes) {
			xfer->frlengths[xfer->aframes] += td->len - len;
			/* manually update data toggle */
			ehci_data_toggle_update(xfer, td->len - len, td->len);
		}

		/* Check for last transfer */
		if (((void *)td) == xfer->td_transfer_last) {
			td = NULL;
			break;
		}
		/* Check for transfer error */
		if (status & EHCI_QTD_HALTED) {
			/* the transfer is finished */
			td = NULL;
			break;
		}
		/* Check for short transfer */
		if (len > 0) {
			if (xfer->flags_int.short_frames_ok) {
				/* follow alt next */
				td = td->alt_next;
			} else {
				/* the transfer is finished */
				td = NULL;
			}
			break;
		}
		td = td->obj_next;

		if (td->alt_next != td_alt_next) {
			/* this USB frame is complete */
			break;
		}
	}

	/* update transfer cache */

	xfer->td_transfer_cache = td;

#ifdef USB_DEBUG
	if (status & EHCI_QTD_STATERRS) {
		DPRINTFN(11, "error, addr=%d, endpt=0x%02x, frame=0x%02x"
		    "status=%s%s%s%s%s%s%s%s\n",
		    xfer->address, xfer->endpointno, xfer->aframes,
		    (status & EHCI_QTD_ACTIVE) ? "[ACTIVE]" : "[NOT_ACTIVE]",
		    (status & EHCI_QTD_HALTED) ? "[HALTED]" : "",
		    (status & EHCI_QTD_BUFERR) ? "[BUFERR]" : "",
		    (status & EHCI_QTD_BABBLE) ? "[BABBLE]" : "",
		    (status & EHCI_QTD_XACTERR) ? "[XACTERR]" : "",
		    (status & EHCI_QTD_MISSEDMICRO) ? "[MISSED]" : "",
		    (status & EHCI_QTD_SPLITXSTATE) ? "[SPLIT]" : "",
		    (status & EHCI_QTD_PINGSTATE) ? "[PING]" : "");
	}
#endif
	if (status & EHCI_QTD_HALTED) {
		if ((xfer->xroot->udev->parent_hs_hub != NULL) ||
		    (xfer->xroot->udev->address != 0)) {
			/* try to separate I/O errors from STALL */
			if (EHCI_QTD_GET_CERR(status) == 0)
				return (USB_ERR_IOERROR);
		}
		return (USB_ERR_STALLED);
	}
	return (USB_ERR_NORMAL_COMPLETION);
}