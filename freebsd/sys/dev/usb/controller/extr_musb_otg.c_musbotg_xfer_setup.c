#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ usb_mode; } ;
struct usb_xfer {scalar_t__ nframes; int endpointno; int max_packet_size; int max_packet_count; void** td_start; int /*<<< orphan*/  max_frame_size; TYPE_1__ flags_int; } ;
struct usb_setup_params {int hc_max_packet_size; int hc_max_frame_size; int hc_max_packet_count; int* size; scalar_t__ buf; scalar_t__ err; TYPE_2__* udev; int /*<<< orphan*/ * methods; struct usb_xfer* curr_xfer; } ;
struct usb_hw_ep_profile {int dummy; } ;
struct musbotg_td {int reg_max_packet; int ep_no; void* obj_next; int /*<<< orphan*/  max_frame_size; } ;
struct musbotg_softc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 struct musbotg_softc* MUSBOTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int UE_ADDR ; 
 struct musbotg_td* USB_ADD_BYTES (scalar_t__,int) ; 
 scalar_t__ USB_ERR_INVAL ; 
 int USB_HOST_ALIGN ; 
 scalar_t__ USB_MODE_DEVICE ; 
 int /*<<< orphan*/  musbotg_device_bulk_methods ; 
 int /*<<< orphan*/  musbotg_device_ctrl_methods ; 
 int /*<<< orphan*/  musbotg_device_intr_methods ; 
 int /*<<< orphan*/  musbotg_device_isoc_methods ; 
 int /*<<< orphan*/  musbotg_get_hw_ep_profile (TYPE_2__*,struct usb_hw_ep_profile const**,int) ; 
 int /*<<< orphan*/  usbd_transfer_setup_sub (struct usb_setup_params*) ; 

__attribute__((used)) static void
musbotg_xfer_setup(struct usb_setup_params *parm)
{
	struct musbotg_softc *sc;
	struct usb_xfer *xfer;
	void *last_obj;
	uint32_t ntd;
	uint32_t n;
	uint8_t ep_no;

	sc = MUSBOTG_BUS2SC(parm->udev->bus);
	xfer = parm->curr_xfer;

	/*
	 * NOTE: This driver does not use any of the parameters that
	 * are computed from the following values. Just set some
	 * reasonable dummies:
	 */
	parm->hc_max_packet_size = 0x400;
	parm->hc_max_frame_size = 0xc00;

	if ((parm->methods == &musbotg_device_isoc_methods) ||
	    (parm->methods == &musbotg_device_intr_methods))
		parm->hc_max_packet_count = 3;
	else
		parm->hc_max_packet_count = 1;

	usbd_transfer_setup_sub(parm);

	/*
	 * compute maximum number of TDs
	 */
	if (parm->methods == &musbotg_device_ctrl_methods) {

		ntd = xfer->nframes + 1 /* STATUS */ + 1 /* SYNC */ ;

	} else if (parm->methods == &musbotg_device_bulk_methods) {

		ntd = xfer->nframes + 1 /* SYNC */ ;

	} else if (parm->methods == &musbotg_device_intr_methods) {

		ntd = xfer->nframes + 1 /* SYNC */ ;

	} else if (parm->methods == &musbotg_device_isoc_methods) {

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

	ep_no = xfer->endpointno & UE_ADDR;

	/*
	 * Check for a valid endpoint profile in USB device mode:
	 */
	if (xfer->flags_int.usb_mode == USB_MODE_DEVICE) {
		const struct usb_hw_ep_profile *pf;

		musbotg_get_hw_ep_profile(parm->udev, &pf, ep_no);

		if (pf == NULL) {
			/* should not happen */
			parm->err = USB_ERR_INVAL;
			return;
		}
	}

	/* align data */
	parm->size[0] += ((-parm->size[0]) & (USB_HOST_ALIGN - 1));

	for (n = 0; n != ntd; n++) {

		struct musbotg_td *td;

		if (parm->buf) {

			td = USB_ADD_BYTES(parm->buf, parm->size[0]);

			/* init TD */
			td->max_frame_size = xfer->max_frame_size;
			td->reg_max_packet = xfer->max_packet_size |
			    ((xfer->max_packet_count - 1) << 11);
			td->ep_no = ep_no;
			td->obj_next = last_obj;

			last_obj = td;
		}
		parm->size[0] += sizeof(*td);
	}

	xfer->td_start[0] = last_obj;
}