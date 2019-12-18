#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int bdma_enable; size_t curr_dma_set; } ;
struct usb_xfer {int nframes; int max_data_length; int max_hc_frame_size; TYPE_1__ flags_int; void** qh_start; void** td_start; } ;
struct usb_setup_params {int hc_max_packet_size; int hc_max_packet_count; int hc_max_frame_size; scalar_t__ buf; void* err; int /*<<< orphan*/ * methods; struct usb_xfer* curr_xfer; } ;
struct usb_page_search {int /*<<< orphan*/  physaddr; TYPE_2__* buffer; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_6__ {struct usb_page_cache* page_cache; void* obj_next; void* ed_self; void* itd_self; void* td_self; } ;
typedef  TYPE_2__ ohci_td_t ;
typedef  TYPE_2__ ohci_itd_t ;
typedef  TYPE_2__ ohci_ed_t ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_ED_ALIGN ; 
 int /*<<< orphan*/  OHCI_ITD_ALIGN ; 
 int /*<<< orphan*/  OHCI_ITD_NOFFSET ; 
 int OHCI_PAGE_SIZE ; 
 int /*<<< orphan*/  OHCI_TD_ALIGN ; 
 void* USB_ERR_NOMEM ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_device_bulk_methods ; 
 int /*<<< orphan*/  ohci_device_ctrl_methods ; 
 int /*<<< orphan*/  ohci_device_intr_methods ; 
 int /*<<< orphan*/  ohci_device_isoc_methods ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (struct usb_page_cache*) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_page_search*) ; 
 int /*<<< orphan*/  usbd_transfer_setup_sub (struct usb_setup_params*) ; 
 scalar_t__ usbd_transfer_setup_sub_malloc (struct usb_setup_params*,struct usb_page_cache**,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ohci_xfer_setup(struct usb_setup_params *parm)
{
	struct usb_page_search page_info;
	struct usb_page_cache *pc;
	struct usb_xfer *xfer;
	void *last_obj;
	uint32_t ntd;
	uint32_t nitd;
	uint32_t nqh;
	uint32_t n;

	xfer = parm->curr_xfer;

	parm->hc_max_packet_size = 0x500;
	parm->hc_max_packet_count = 1;
	parm->hc_max_frame_size = OHCI_PAGE_SIZE;

	/*
	 * calculate ntd and nqh
	 */
	if (parm->methods == &ohci_device_ctrl_methods) {
		xfer->flags_int.bdma_enable = 1;

		usbd_transfer_setup_sub(parm);

		nitd = 0;
		ntd = ((2 * xfer->nframes) + 1	/* STATUS */
		    + (xfer->max_data_length / xfer->max_hc_frame_size));
		nqh = 1;

	} else if (parm->methods == &ohci_device_bulk_methods) {
		xfer->flags_int.bdma_enable = 1;

		usbd_transfer_setup_sub(parm);

		nitd = 0;
		ntd = ((2 * xfer->nframes)
		    + (xfer->max_data_length / xfer->max_hc_frame_size));
		nqh = 1;

	} else if (parm->methods == &ohci_device_intr_methods) {
		xfer->flags_int.bdma_enable = 1;

		usbd_transfer_setup_sub(parm);

		nitd = 0;
		ntd = ((2 * xfer->nframes)
		    + (xfer->max_data_length / xfer->max_hc_frame_size));
		nqh = 1;

	} else if (parm->methods == &ohci_device_isoc_methods) {
		xfer->flags_int.bdma_enable = 1;

		usbd_transfer_setup_sub(parm);

		nitd = ((xfer->max_data_length / OHCI_PAGE_SIZE) +
		    howmany(xfer->nframes, OHCI_ITD_NOFFSET) +
		    1 /* EXTRA */ );
		ntd = 0;
		nqh = 1;

	} else {

		usbd_transfer_setup_sub(parm);

		nitd = 0;
		ntd = 0;
		nqh = 0;
	}

alloc_dma_set:

	if (parm->err) {
		return;
	}
	last_obj = NULL;

	if (usbd_transfer_setup_sub_malloc(
	    parm, &pc, sizeof(ohci_td_t),
	    OHCI_TD_ALIGN, ntd)) {
		parm->err = USB_ERR_NOMEM;
		return;
	}
	if (parm->buf) {
		for (n = 0; n != ntd; n++) {
			ohci_td_t *td;

			usbd_get_page(pc + n, 0, &page_info);

			td = page_info.buffer;

			/* init TD */
			td->td_self = htole32(page_info.physaddr);
			td->obj_next = last_obj;
			td->page_cache = pc + n;

			last_obj = td;

			usb_pc_cpu_flush(pc + n);
		}
	}
	if (usbd_transfer_setup_sub_malloc(
	    parm, &pc, sizeof(ohci_itd_t),
	    OHCI_ITD_ALIGN, nitd)) {
		parm->err = USB_ERR_NOMEM;
		return;
	}
	if (parm->buf) {
		for (n = 0; n != nitd; n++) {
			ohci_itd_t *itd;

			usbd_get_page(pc + n, 0, &page_info);

			itd = page_info.buffer;

			/* init TD */
			itd->itd_self = htole32(page_info.physaddr);
			itd->obj_next = last_obj;
			itd->page_cache = pc + n;

			last_obj = itd;

			usb_pc_cpu_flush(pc + n);
		}
	}
	xfer->td_start[xfer->flags_int.curr_dma_set] = last_obj;

	last_obj = NULL;

	if (usbd_transfer_setup_sub_malloc(
	    parm, &pc, sizeof(ohci_ed_t),
	    OHCI_ED_ALIGN, nqh)) {
		parm->err = USB_ERR_NOMEM;
		return;
	}
	if (parm->buf) {
		for (n = 0; n != nqh; n++) {
			ohci_ed_t *ed;

			usbd_get_page(pc + n, 0, &page_info);

			ed = page_info.buffer;

			/* init QH */
			ed->ed_self = htole32(page_info.physaddr);
			ed->obj_next = last_obj;
			ed->page_cache = pc + n;

			last_obj = ed;

			usb_pc_cpu_flush(pc + n);
		}
	}
	xfer->qh_start[xfer->flags_int.curr_dma_set] = last_obj;

	if (!xfer->flags_int.curr_dma_set) {
		xfer->flags_int.curr_dma_set = 1;
		goto alloc_dma_set;
	}
}