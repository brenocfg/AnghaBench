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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct xhci_td {scalar_t__ status; scalar_t__ remainder; scalar_t__ len; struct xhci_td* alt_next; struct xhci_td* obj_next; int /*<<< orphan*/  page_cache; } ;
struct TYPE_2__ {scalar_t__ control_xfr; scalar_t__ isochronous_xfr; scalar_t__ short_frames_ok; } ;
struct usb_xfer {size_t aframes; size_t nframes; void* td_transfer_last; struct xhci_td* td_transfer_cache; TYPE_1__ flags_int; int /*<<< orphan*/ * frlengths; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_xfer*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  USB_ERR_IOERROR ; 
 int /*<<< orphan*/  USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  USB_ERR_STALLED ; 
 scalar_t__ XHCI_TRB_ERROR_LENGTH ; 
 scalar_t__ XHCI_TRB_ERROR_SHORT_PKT ; 
 scalar_t__ XHCI_TRB_ERROR_STALL ; 
 scalar_t__ XHCI_TRB_ERROR_SUCCESS ; 
 int /*<<< orphan*/  usb_pc_cpu_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
xhci_generic_done_sub(struct usb_xfer *xfer)
{
	struct xhci_td *td;
	struct xhci_td *td_alt_next;
	uint32_t len;
	uint8_t status;

	td = xfer->td_transfer_cache;
	td_alt_next = td->alt_next;

	if (xfer->aframes != xfer->nframes)
		usbd_xfer_set_frame_len(xfer, xfer->aframes, 0);

	while (1) {

		usb_pc_cpu_invalidate(td->page_cache);

		status = td->status;
		len = td->remainder;

		DPRINTFN(4, "xfer=%p[%u/%u] rem=%u/%u status=%u\n",
		    xfer, (unsigned int)xfer->aframes,
		    (unsigned int)xfer->nframes,
		    (unsigned int)len, (unsigned int)td->len,
		    (unsigned int)status);

		/*
	         * Verify the status length and
		 * add the length to "frlengths[]":
	         */
		if (len > td->len) {
			/* should not happen */
			DPRINTF("Invalid status length, "
			    "0x%04x/0x%04x bytes\n", len, td->len);
			status = XHCI_TRB_ERROR_LENGTH;
		} else if (xfer->aframes != xfer->nframes) {
			xfer->frlengths[xfer->aframes] += td->len - len;
		}
		/* Check for last transfer */
		if (((void *)td) == xfer->td_transfer_last) {
			td = NULL;
			break;
		}
		/* Check for transfer error */
		if (status != XHCI_TRB_ERROR_SHORT_PKT &&
		    status != XHCI_TRB_ERROR_SUCCESS) {
			/* the transfer is finished */
			td = NULL;
			break;
		}
		/* Check for short transfer */
		if (len > 0) {
			if (xfer->flags_int.short_frames_ok || 
			    xfer->flags_int.isochronous_xfr ||
			    xfer->flags_int.control_xfr) {
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

	return ((status == XHCI_TRB_ERROR_STALL) ? USB_ERR_STALLED : 
	    (status != XHCI_TRB_ERROR_SHORT_PKT && 
	    status != XHCI_TRB_ERROR_SUCCESS) ? USB_ERR_IOERROR :
	    USB_ERR_NORMAL_COMPLETION);
}