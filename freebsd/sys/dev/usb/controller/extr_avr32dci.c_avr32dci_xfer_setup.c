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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct usb_xfer {scalar_t__ nframes; int endpointno; void** td_start; int /*<<< orphan*/  max_packet_size; TYPE_2__* endpoint; } ;
struct usb_setup_params {int hc_max_packet_size; int hc_max_packet_count; int hc_max_frame_size; int* size; scalar_t__ buf; scalar_t__ err; TYPE_3__* udev; struct usb_xfer* curr_xfer; } ;
struct usb_hw_ep_profile {scalar_t__ max_in_frame_size; scalar_t__ max_out_frame_size; scalar_t__ support_multi_buffer; } ;
struct avr32dci_td {int ep_no; int support_multi_buffer; void* obj_next; scalar_t__ bank_shift; int /*<<< orphan*/  max_packet_size; } ;
struct avr32dci_softc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bus; } ;
struct TYPE_5__ {TYPE_1__* edesc; } ;
struct TYPE_4__ {int bmAttributes; } ;

/* Variables and functions */
 struct avr32dci_softc* AVR32_BUS2SC (int /*<<< orphan*/ ) ; 
 int UE_ADDR ; 
 int UE_CONTROL ; 
 int UE_XFERTYPE ; 
 struct avr32dci_td* USB_ADD_BYTES (scalar_t__,int) ; 
 scalar_t__ USB_ERR_INVAL ; 
 int USB_HOST_ALIGN ; 
 int /*<<< orphan*/  avr32dci_get_hw_ep_profile (TYPE_3__*,struct usb_hw_ep_profile const**,int) ; 
 int /*<<< orphan*/  usbd_transfer_setup_sub (struct usb_setup_params*) ; 

__attribute__((used)) static void
avr32dci_xfer_setup(struct usb_setup_params *parm)
{
	const struct usb_hw_ep_profile *pf;
	struct avr32dci_softc *sc;
	struct usb_xfer *xfer;
	void *last_obj;
	uint32_t ntd;
	uint32_t n;
	uint8_t ep_no;

	sc = AVR32_BUS2SC(parm->udev->bus);
	xfer = parm->curr_xfer;

	/*
	 * NOTE: This driver does not use any of the parameters that
	 * are computed from the following values. Just set some
	 * reasonable dummies:
	 */
	parm->hc_max_packet_size = 0x400;
	parm->hc_max_packet_count = 1;
	parm->hc_max_frame_size = 0x400;

	usbd_transfer_setup_sub(parm);

	/*
	 * compute maximum number of TDs
	 */
	if ((xfer->endpoint->edesc->bmAttributes & UE_XFERTYPE) == UE_CONTROL) {

		ntd = xfer->nframes + 1 /* STATUS */ + 1	/* SYNC 1 */
		    + 1 /* SYNC 2 */ ;
	} else {

		ntd = xfer->nframes + 1 /* SYNC */ ;
	}

	/*
	 * check if "usbd_transfer_setup_sub" set an error
	 */
	if (parm->err)
		return;

	/*
	 * allocate transfer descriptors
	 */
	last_obj = NULL;

	/*
	 * get profile stuff
	 */
	ep_no = xfer->endpointno & UE_ADDR;
	avr32dci_get_hw_ep_profile(parm->udev, &pf, ep_no);

	if (pf == NULL) {
		/* should not happen */
		parm->err = USB_ERR_INVAL;
		return;
	}
	/* align data */
	parm->size[0] += ((-parm->size[0]) & (USB_HOST_ALIGN - 1));

	for (n = 0; n != ntd; n++) {

		struct avr32dci_td *td;

		if (parm->buf) {
			uint32_t temp;

			td = USB_ADD_BYTES(parm->buf, parm->size[0]);

			/* init TD */
			td->max_packet_size = xfer->max_packet_size;
			td->ep_no = ep_no;
			temp = pf->max_in_frame_size | pf->max_out_frame_size;
			td->bank_shift = 0;
			while ((temp /= 2))
				td->bank_shift++;
			if (pf->support_multi_buffer) {
				td->support_multi_buffer = 1;
			}
			td->obj_next = last_obj;

			last_obj = td;
		}
		parm->size[0] += sizeof(*td);
	}

	xfer->td_start[0] = last_obj;
}