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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct uss820dci_td {int ep_index; int support_multi_buffer; void* obj_next; int /*<<< orphan*/  max_packet_size; } ;
struct uss820dci_softc {int dummy; } ;
struct usb_xfer {scalar_t__ nframes; int endpointno; void** td_start; int /*<<< orphan*/  max_packet_size; } ;
struct usb_setup_params {int hc_max_packet_size; int hc_max_packet_count; int hc_max_frame_size; int* size; int /*<<< orphan*/ * methods; scalar_t__ buf; scalar_t__ err; TYPE_1__* udev; struct usb_xfer* curr_xfer; } ;
struct usb_hw_ep_profile {scalar_t__ support_multi_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int UE_ADDR ; 
 struct uss820dci_td* USB_ADD_BYTES (scalar_t__,int) ; 
 scalar_t__ USB_ERR_INVAL ; 
 int USB_HOST_ALIGN ; 
 struct uss820dci_softc* USS820_DCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_setup_sub (struct usb_setup_params*) ; 
 int /*<<< orphan*/  uss820dci_device_bulk_methods ; 
 int /*<<< orphan*/  uss820dci_device_ctrl_methods ; 
 int /*<<< orphan*/  uss820dci_device_intr_methods ; 
 int /*<<< orphan*/  uss820dci_device_isoc_fs_methods ; 
 int /*<<< orphan*/  uss820dci_get_hw_ep_profile (TYPE_1__*,struct usb_hw_ep_profile const**,int) ; 

__attribute__((used)) static void
uss820dci_xfer_setup(struct usb_setup_params *parm)
{
	const struct usb_hw_ep_profile *pf;
	struct uss820dci_softc *sc;
	struct usb_xfer *xfer;
	void *last_obj;
	uint32_t ntd;
	uint32_t n;
	uint8_t ep_no;

	sc = USS820_DCI_BUS2SC(parm->udev->bus);
	xfer = parm->curr_xfer;

	/*
	 * NOTE: This driver does not use any of the parameters that
	 * are computed from the following values. Just set some
	 * reasonable dummies:
	 */
	parm->hc_max_packet_size = 0x500;
	parm->hc_max_packet_count = 1;
	parm->hc_max_frame_size = 0x500;

	usbd_transfer_setup_sub(parm);

	/*
	 * compute maximum number of TDs
	 */
	if (parm->methods == &uss820dci_device_ctrl_methods) {

		ntd = xfer->nframes + 1 /* STATUS */ + 1 /* SYNC */ ;

	} else if (parm->methods == &uss820dci_device_bulk_methods) {

		ntd = xfer->nframes + 1 /* SYNC */ ;

	} else if (parm->methods == &uss820dci_device_intr_methods) {

		ntd = xfer->nframes + 1 /* SYNC */ ;

	} else if (parm->methods == &uss820dci_device_isoc_fs_methods) {

		ntd = xfer->nframes + 1 /* SYNC */ ;

	} else {

		ntd = 0;
	}

	/*
	 * check if "usbd_transfer_setup_sub" set an error
	 */
	if (parm->err) {
		return;
	}
	/*
	 * allocate transfer descriptors
	 */
	last_obj = NULL;

	/*
	 * get profile stuff
	 */
	if (ntd) {

		ep_no = xfer->endpointno & UE_ADDR;
		uss820dci_get_hw_ep_profile(parm->udev, &pf, ep_no);

		if (pf == NULL) {
			/* should not happen */
			parm->err = USB_ERR_INVAL;
			return;
		}
	} else {
		ep_no = 0;
		pf = NULL;
	}

	/* align data */
	parm->size[0] += ((-parm->size[0]) & (USB_HOST_ALIGN - 1));

	for (n = 0; n != ntd; n++) {

		struct uss820dci_td *td;

		if (parm->buf) {

			td = USB_ADD_BYTES(parm->buf, parm->size[0]);

			/* init TD */
			td->max_packet_size = xfer->max_packet_size;
			td->ep_index = ep_no;
			if (pf->support_multi_buffer &&
			    (parm->methods != &uss820dci_device_ctrl_methods)) {
				td->support_multi_buffer = 1;
			}
			td->obj_next = last_obj;

			last_obj = td;
		}
		parm->size[0] += sizeof(*td);
	}

	xfer->td_start[0] = last_obj;
}