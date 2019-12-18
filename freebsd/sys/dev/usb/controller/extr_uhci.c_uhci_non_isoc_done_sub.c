#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {scalar_t__ len; struct TYPE_6__* alt_next; struct TYPE_6__* obj_next; scalar_t__ fix_pc; int /*<<< orphan*/  td_token; int /*<<< orphan*/  td_status; scalar_t__ page_cache; } ;
typedef  TYPE_3__ uhci_td_t ;
struct TYPE_4__ {scalar_t__ short_frames_ok; } ;
struct usb_xfer {size_t aframes; size_t nframes; void* td_transfer_last; int /*<<< orphan*/  endpointno; int /*<<< orphan*/  address; TYPE_2__* endpoint; TYPE_3__* td_transfer_cache; TYPE_1__ flags_int; int /*<<< orphan*/ * frlengths; scalar_t__ frbuffers; } ;
struct usb_page_search {int /*<<< orphan*/  buffer; } ;
struct TYPE_5__ {int toggle_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int UHCI_TD_ACTIVE ; 
 int UHCI_TD_BABBLE ; 
 int UHCI_TD_BITSTUFF ; 
 int UHCI_TD_CRCTO ; 
 int UHCI_TD_DBUFFER ; 
 int UHCI_TD_ERROR ; 
 scalar_t__ UHCI_TD_GET_ACTLEN (int) ; 
 scalar_t__ UHCI_TD_GET_ERRCNT (int) ; 
 int UHCI_TD_IOC ; 
 int UHCI_TD_IOS ; 
 int UHCI_TD_LS ; 
 int UHCI_TD_NAK ; 
 int UHCI_TD_SET_DT (int) ; 
 int UHCI_TD_SPD ; 
 int UHCI_TD_STALLED ; 
 int /*<<< orphan*/  USB_ERR_IOERROR ; 
 int /*<<< orphan*/  USB_ERR_NORMAL_COMPLETION ; 
 int /*<<< orphan*/  USB_ERR_STALLED ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pc_cpu_invalidate (scalar_t__) ; 
 int /*<<< orphan*/  usbd_copy_in (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usbd_get_page (scalar_t__,int /*<<< orphan*/ ,struct usb_page_search*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
uhci_non_isoc_done_sub(struct usb_xfer *xfer)
{
	struct usb_page_search res;
	uhci_td_t *td;
	uhci_td_t *td_alt_next;
	uint32_t status;
	uint32_t token;
	uint16_t len;

	td = xfer->td_transfer_cache;
	td_alt_next = td->alt_next;

	if (xfer->aframes != xfer->nframes) {
		usbd_xfer_set_frame_len(xfer, xfer->aframes, 0);
	}
	while (1) {

		usb_pc_cpu_invalidate(td->page_cache);
		status = le32toh(td->td_status);
		token = le32toh(td->td_token);

		/*
	         * Verify the status and add
	         * up the actual length:
	         */

		len = UHCI_TD_GET_ACTLEN(status);
		if (len > td->len) {
			/* should not happen */
			DPRINTF("Invalid status length, "
			    "0x%04x/0x%04x bytes\n", len, td->len);
			status |= UHCI_TD_STALLED;

		} else if ((xfer->aframes != xfer->nframes) && (len > 0)) {

			if (td->fix_pc) {

				usbd_get_page(td->fix_pc, 0, &res);

				/*
				 * copy data from fixup location to real
				 * location
				 */

				usb_pc_cpu_invalidate(td->fix_pc);

				usbd_copy_in(xfer->frbuffers + xfer->aframes,
				    xfer->frlengths[xfer->aframes], res.buffer, len);
			}
			/* update actual length */

			xfer->frlengths[xfer->aframes] += len;
		}
		/* Check for last transfer */
		if (((void *)td) == xfer->td_transfer_last) {
			td = NULL;
			break;
		}
		if (status & UHCI_TD_STALLED) {
			/* the transfer is finished */
			td = NULL;
			break;
		}
		/* Check for short transfer */
		if (len != td->len) {
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

	/* update data toggle */

	xfer->endpoint->toggle_next = (token & UHCI_TD_SET_DT(1)) ? 0 : 1;

#ifdef USB_DEBUG
	if (status & UHCI_TD_ERROR) {
		DPRINTFN(11, "error, addr=%d, endpt=0x%02x, frame=0x%02x "
		    "status=%s%s%s%s%s%s%s%s%s%s%s\n",
		    xfer->address, xfer->endpointno, xfer->aframes,
		    (status & UHCI_TD_BITSTUFF) ? "[BITSTUFF]" : "",
		    (status & UHCI_TD_CRCTO) ? "[CRCTO]" : "",
		    (status & UHCI_TD_NAK) ? "[NAK]" : "",
		    (status & UHCI_TD_BABBLE) ? "[BABBLE]" : "",
		    (status & UHCI_TD_DBUFFER) ? "[DBUFFER]" : "",
		    (status & UHCI_TD_STALLED) ? "[STALLED]" : "",
		    (status & UHCI_TD_ACTIVE) ? "[ACTIVE]" : "[NOT_ACTIVE]",
		    (status & UHCI_TD_IOC) ? "[IOC]" : "",
		    (status & UHCI_TD_IOS) ? "[IOS]" : "",
		    (status & UHCI_TD_LS) ? "[LS]" : "",
		    (status & UHCI_TD_SPD) ? "[SPD]" : "");
	}
#endif
	if (status & UHCI_TD_STALLED) {
		/* try to separate I/O errors from STALL */
		if (UHCI_TD_GET_ERRCNT(status) == 0)
			return (USB_ERR_IOERROR);
		return (USB_ERR_STALLED);
	}
	return (USB_ERR_NORMAL_COMPLETION);
}