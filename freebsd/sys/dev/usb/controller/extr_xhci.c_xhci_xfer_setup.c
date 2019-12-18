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
typedef  int uint32_t ;
struct xhci_td {struct usb_page_cache* page_cache; void* obj_next; int /*<<< orphan*/  td_self; } ;
struct TYPE_2__ {int bdma_enable; size_t curr_dma_set; scalar_t__ control_xfr; scalar_t__ isochronous_xfr; } ;
struct usb_xfer {int nframes; int max_data_length; int max_hc_frame_size; TYPE_1__ flags_int; void** td_start; } ;
struct usb_setup_params {int hc_max_packet_size; int hc_max_packet_count; scalar_t__ buf; scalar_t__ err; int /*<<< orphan*/  hc_max_frame_size; struct usb_xfer* curr_xfer; } ;
struct usb_page_search {int /*<<< orphan*/  physaddr; struct xhci_td* buffer; } ;
struct usb_page_cache {int dummy; } ;

/* Variables and functions */
 scalar_t__ USB_ERR_NOMEM ; 
 int /*<<< orphan*/  XHCI_TD_ALIGN ; 
 int /*<<< orphan*/  XHCI_TD_PAYLOAD_MAX ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (struct usb_page_cache*) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_page_search*) ; 
 int /*<<< orphan*/  usbd_transfer_setup_sub (struct usb_setup_params*) ; 
 scalar_t__ usbd_transfer_setup_sub_malloc (struct usb_setup_params*,struct usb_page_cache**,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xhci_xfer_setup(struct usb_setup_params *parm)
{
	struct usb_page_search page_info;
	struct usb_page_cache *pc;
	struct usb_xfer *xfer;
	void *last_obj;
	uint32_t ntd;
	uint32_t n;

	xfer = parm->curr_xfer;

	/*
	 * The proof for the "ntd" formula is illustrated like this:
	 *
	 * +------------------------------------+
	 * |                                    |
	 * |         |remainder ->              |
	 * |   +-----+---+                      |
	 * |   | xxx | x | frm 0                |
	 * |   +-----+---++                     |
	 * |   | xxx | xx | frm 1               |
	 * |   +-----+----+                     |
	 * |            ...                     |
	 * +------------------------------------+
	 *
	 * "xxx" means a completely full USB transfer descriptor
	 *
	 * "x" and "xx" means a short USB packet
	 *
	 * For the remainder of an USB transfer modulo
	 * "max_data_length" we need two USB transfer descriptors.
	 * One to transfer the remaining data and one to finalise with
	 * a zero length packet in case the "force_short_xfer" flag is
	 * set. We only need two USB transfer descriptors in the case
	 * where the transfer length of the first one is a factor of
	 * "max_frame_size". The rest of the needed USB transfer
	 * descriptors is given by the buffer size divided by the
	 * maximum data payload.
	 */
	parm->hc_max_packet_size = 0x400;
	parm->hc_max_packet_count = 16 * 3;
	parm->hc_max_frame_size = XHCI_TD_PAYLOAD_MAX;

	xfer->flags_int.bdma_enable = 1;

	usbd_transfer_setup_sub(parm);

	if (xfer->flags_int.isochronous_xfr) {
		ntd = ((1 * xfer->nframes)
		    + (xfer->max_data_length / xfer->max_hc_frame_size));
	} else if (xfer->flags_int.control_xfr) {
		ntd = ((2 * xfer->nframes) + 1	/* STATUS */
		    + (xfer->max_data_length / xfer->max_hc_frame_size));
	} else {
		ntd = ((2 * xfer->nframes)
		    + (xfer->max_data_length / xfer->max_hc_frame_size));
	}

alloc_dma_set:

	if (parm->err)
		return;

	/*
	 * Allocate queue heads and transfer descriptors
	 */
	last_obj = NULL;

	if (usbd_transfer_setup_sub_malloc(
	    parm, &pc, sizeof(struct xhci_td),
	    XHCI_TD_ALIGN, ntd)) {
		parm->err = USB_ERR_NOMEM;
		return;
	}
	if (parm->buf) {
		for (n = 0; n != ntd; n++) {
			struct xhci_td *td;

			usbd_get_page(pc + n, 0, &page_info);

			td = page_info.buffer;

			/* init TD */
			td->td_self = page_info.physaddr;
			td->obj_next = last_obj;
			td->page_cache = pc + n;

			last_obj = td;

			usb_pc_cpu_flush(pc + n);
		}
	}
	xfer->td_start[xfer->flags_int.curr_dma_set] = last_obj;

	if (!xfer->flags_int.curr_dma_set) {
		xfer->flags_int.curr_dma_set = 1;
		goto alloc_dma_set;
	}
}