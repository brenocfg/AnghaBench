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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct usb_xfer {int nframes; int endpointno; int address; int interval; void** td_start; int /*<<< orphan*/  max_packet_size; TYPE_2__* endpoint; } ;
struct usb_setup_params {int hc_max_packet_size; int hc_max_packet_count; int hc_max_frame_size; int* size; scalar_t__ buf; TYPE_4__* udev; scalar_t__ err; struct usb_xfer* curr_xfer; } ;
struct usb_hw_ep_profile {int dummy; } ;
struct saf1761_otg_td {int ep_index; int ep_type; int dw1_value; int interval; void* obj_next; scalar_t__ uframe; int /*<<< orphan*/  max_packet_size; } ;
struct saf1761_otg_softc {int dummy; } ;
struct TYPE_7__ {scalar_t__ usb_mode; } ;
struct TYPE_8__ {int speed; int hs_port_no; int hs_hub_addr; int /*<<< orphan*/ * parent_hs_hub; TYPE_3__ flags; int /*<<< orphan*/  bus; } ;
struct TYPE_6__ {TYPE_1__* edesc; } ;
struct TYPE_5__ {int bmAttributes; } ;

/* Variables and functions */
 struct saf1761_otg_softc* SAF1761_OTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int SOTG_PTD_DW1_ENABLE_SPLIT ; 
 int UE_ADDR ; 
 int UE_CONTROL ; 
 int UE_INTERRUPT ; 
 int UE_XFERTYPE ; 
 struct saf1761_otg_td* USB_ADD_BYTES (scalar_t__,int) ; 
 scalar_t__ USB_ERR_INVAL ; 
 int USB_HOST_ALIGN ; 
 scalar_t__ USB_MODE_DEVICE ; 
#define  USB_SPEED_FULL 129 
#define  USB_SPEED_LOW 128 
 int /*<<< orphan*/  saf1761_otg_get_hw_ep_profile (TYPE_4__*,struct usb_hw_ep_profile const**,int) ; 
 int /*<<< orphan*/  usbd_transfer_setup_sub (struct usb_setup_params*) ; 

__attribute__((used)) static void
saf1761_otg_xfer_setup(struct usb_setup_params *parm)
{
	struct saf1761_otg_softc *sc;
	struct usb_xfer *xfer;
	void *last_obj;
	uint32_t dw1;
	uint32_t ntd;
	uint32_t n;
	uint8_t ep_no;
	uint8_t ep_type;

	sc = SAF1761_OTG_BUS2SC(parm->udev->bus);
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
	 * Compute maximum number of TDs:
	 */
	ep_type = (xfer->endpoint->edesc->bmAttributes & UE_XFERTYPE);

	if (ep_type == UE_CONTROL) {

		ntd = xfer->nframes + 1 /* STATUS */ + 1 /* SYNC */ ;

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

	ep_no = xfer->endpointno & UE_ADDR;

	/*
	 * Check profile stuff
	 */
	if (parm->udev->flags.usb_mode == USB_MODE_DEVICE) {
		const struct usb_hw_ep_profile *pf;

		saf1761_otg_get_hw_ep_profile(parm->udev, &pf, ep_no);

		if (pf == NULL) {
			/* should not happen */
			parm->err = USB_ERR_INVAL;
			return;
		}
	}

	dw1 = (xfer->address << 3) | (ep_type << 12);

	switch (parm->udev->speed) {
	case USB_SPEED_FULL:
	case USB_SPEED_LOW:
		/* check if root HUB port is running High Speed */
		if (parm->udev->parent_hs_hub != NULL) {
			dw1 |= SOTG_PTD_DW1_ENABLE_SPLIT;
			dw1 |= (parm->udev->hs_port_no << 18);
			dw1 |= (parm->udev->hs_hub_addr << 25);
			if (parm->udev->speed == USB_SPEED_LOW)
				dw1 |= (1 << 17);
		}
		break;
	default:
		break;
	}

	/* align data */
	parm->size[0] += ((-parm->size[0]) & (USB_HOST_ALIGN - 1));

	for (n = 0; n != ntd; n++) {

		struct saf1761_otg_td *td;

		if (parm->buf) {

			td = USB_ADD_BYTES(parm->buf, parm->size[0]);

			/* init TD */
			td->max_packet_size = xfer->max_packet_size;
			td->ep_index = ep_no;
			td->ep_type = ep_type;
			td->dw1_value = dw1;
			td->uframe = 0;

			if (ep_type == UE_INTERRUPT) {
				if (xfer->interval > 32)
					td->interval = (32 / 2) << 3;
				else
					td->interval = (xfer->interval / 2) << 3;
			} else {
				td->interval = 0;
			}
			td->obj_next = last_obj;

			last_obj = td;
		}
		parm->size[0] += sizeof(*td);
	}

	xfer->td_start[0] = last_obj;
}