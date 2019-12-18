#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_11__ {scalar_t__ usb_mode; scalar_t__ control_act; scalar_t__ control_xfr; scalar_t__ isochronous_xfr; scalar_t__ control_hdr; int /*<<< orphan*/  control_stall; scalar_t__ short_frames_ok; } ;
struct TYPE_7__ {scalar_t__ force_short_xfer; } ;
struct usb_xfer {int address; int endpointno; scalar_t__* frlengths; int nframes; struct musbotg_td* td_transfer_last; TYPE_5__ flags_int; int /*<<< orphan*/ * frbuffers; TYPE_1__ flags; TYPE_4__* endpoint; TYPE_3__* xroot; struct musbotg_td** td_start; struct musbotg_td* td_transfer_cache; struct musbotg_td* td_transfer_first; int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  sumlen; } ;
struct musbotg_td {int /*<<< orphan*/  toggle; } ;
struct musbotg_std_temp {scalar_t__ offset; int setup_alt_next; int did_stall; int channel; int dev_addr; int transfer_type; scalar_t__ len; int short_pkt; struct musbotg_td* td; int /*<<< orphan*/ * func; int /*<<< orphan*/ * pc; int /*<<< orphan*/  hport; int /*<<< orphan*/  haddr; struct musbotg_td* td_next; int /*<<< orphan*/  max_frame_size; } ;
struct musbotg_softc {scalar_t__ sc_mode; } ;
typedef  enum usb_dev_speed { ____Placeholder_usb_dev_speed } usb_dev_speed ;
struct TYPE_12__ {int /*<<< orphan*/  hs_port_no; int /*<<< orphan*/  hs_hub_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  toggle_next; TYPE_2__* edesc; } ;
struct TYPE_9__ {TYPE_6__* udev; int /*<<< orphan*/  bus; } ;
struct TYPE_8__ {int bmAttributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int,...) ; 
 scalar_t__ MUSB2_DEVICE_MODE ; 
 int MUSB2_MASK_TI_PROTO_BULK ; 
 int MUSB2_MASK_TI_PROTO_CTRL ; 
 int MUSB2_MASK_TI_PROTO_INTR ; 
 int MUSB2_MASK_TI_PROTO_ISOC ; 
 int MUSB2_MASK_TI_SPEED_FS ; 
 int MUSB2_MASK_TI_SPEED_HS ; 
 int MUSB2_MASK_TI_SPEED_LO ; 
 struct musbotg_softc* MUSBOTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int UE_ADDR ; 
#define  UE_BULK 134 
#define  UE_CONTROL 133 
 int UE_DIR_IN ; 
 int /*<<< orphan*/  UE_GET_ADDR (int) ; 
#define  UE_INTERRUPT 132 
#define  UE_ISOCHRONOUS 131 
 int UE_XFERTYPE ; 
 scalar_t__ USB_MODE_DEVICE ; 
 scalar_t__ USB_MODE_HOST ; 
#define  USB_SPEED_FULL 130 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_LOW 128 
 int /*<<< orphan*/  musbotg_dev_ctrl_data_rx ; 
 int /*<<< orphan*/  musbotg_dev_ctrl_data_tx ; 
 int /*<<< orphan*/  musbotg_dev_ctrl_setup_rx ; 
 int /*<<< orphan*/  musbotg_dev_ctrl_status ; 
 int /*<<< orphan*/  musbotg_dev_data_rx ; 
 int /*<<< orphan*/  musbotg_dev_data_tx ; 
 int /*<<< orphan*/  musbotg_host_ctrl_data_rx ; 
 int /*<<< orphan*/  musbotg_host_ctrl_data_tx ; 
 int /*<<< orphan*/  musbotg_host_ctrl_setup_tx ; 
 int /*<<< orphan*/ * musbotg_host_ctrl_status_rx ; 
 int /*<<< orphan*/ * musbotg_host_ctrl_status_tx ; 
 int /*<<< orphan*/  musbotg_host_data_rx ; 
 int /*<<< orphan*/  musbotg_host_data_tx ; 
 int /*<<< orphan*/  musbotg_setup_standard_chain_sub (struct musbotg_std_temp*) ; 
 int usbd_get_speed (TYPE_6__*) ; 

__attribute__((used)) static void
musbotg_setup_standard_chain(struct usb_xfer *xfer)
{
	struct musbotg_std_temp temp;
	struct musbotg_softc *sc;
	struct musbotg_td *td;
	uint32_t x;
	uint8_t ep_no;
	uint8_t xfer_type;
	enum usb_dev_speed speed;
	int tx;
	int dev_addr;

	DPRINTFN(8, "addr=%d endpt=%d sumlen=%d speed=%d\n",
	    xfer->address, UE_GET_ADDR(xfer->endpointno),
	    xfer->sumlen, usbd_get_speed(xfer->xroot->udev));

	sc = MUSBOTG_BUS2SC(xfer->xroot->bus);
	ep_no = (xfer->endpointno & UE_ADDR);

	temp.max_frame_size = xfer->max_frame_size;

	td = xfer->td_start[0];
	xfer->td_transfer_first = td;
	xfer->td_transfer_cache = td;

	/* setup temp */
	dev_addr = xfer->address;

	xfer_type = xfer->endpoint->edesc->bmAttributes & UE_XFERTYPE;

	temp.pc = NULL;
	temp.td = NULL;
	temp.td_next = xfer->td_start[0];
	temp.offset = 0;
	temp.setup_alt_next = xfer->flags_int.short_frames_ok ||
	    xfer->flags_int.isochronous_xfr;
	temp.did_stall = !xfer->flags_int.control_stall;
	temp.channel = -1;
	temp.dev_addr = dev_addr;
	temp.haddr = xfer->xroot->udev->hs_hub_addr;
	temp.hport = xfer->xroot->udev->hs_port_no;

	if (xfer->flags_int.usb_mode == USB_MODE_HOST) {
		speed =  usbd_get_speed(xfer->xroot->udev);

		switch (speed) {
			case USB_SPEED_LOW:
				temp.transfer_type = MUSB2_MASK_TI_SPEED_LO;
				break;
			case USB_SPEED_FULL:
				temp.transfer_type = MUSB2_MASK_TI_SPEED_FS;
				break;
			case USB_SPEED_HIGH:
				temp.transfer_type = MUSB2_MASK_TI_SPEED_HS;
				break;
			default:
				temp.transfer_type = 0;
				DPRINTFN(-1, "Invalid USB speed: %d\n", speed);
				break;
		}

		switch (xfer_type) {
			case UE_CONTROL:
				temp.transfer_type |= MUSB2_MASK_TI_PROTO_CTRL;
				break;
			case UE_ISOCHRONOUS:
				temp.transfer_type |= MUSB2_MASK_TI_PROTO_ISOC;
				break;
			case UE_BULK:
				temp.transfer_type |= MUSB2_MASK_TI_PROTO_BULK;
				break;
			case UE_INTERRUPT:
				temp.transfer_type |= MUSB2_MASK_TI_PROTO_INTR;
				break;
			default:
				DPRINTFN(-1, "Invalid USB transfer type: %d\n",
						xfer_type);
				break;
		}

		temp.transfer_type |= ep_no;
		td->toggle = xfer->endpoint->toggle_next;
	}

	/* check if we should prepend a setup message */

	if (xfer->flags_int.control_xfr) {
		if (xfer->flags_int.control_hdr) {

			if (xfer->flags_int.usb_mode == USB_MODE_DEVICE)
				temp.func = &musbotg_dev_ctrl_setup_rx;
			else
				temp.func = &musbotg_host_ctrl_setup_tx;

			temp.len = xfer->frlengths[0];
			temp.pc = xfer->frbuffers + 0;
			temp.short_pkt = temp.len ? 1 : 0;

			musbotg_setup_standard_chain_sub(&temp);
		}
		x = 1;
	} else {
		x = 0;
	}

	tx = 0;

	if (x != xfer->nframes) {
		if (xfer->endpointno & UE_DIR_IN)
		    	tx = 1;

		if (xfer->flags_int.usb_mode == USB_MODE_HOST) {
			tx = !tx;

			if (tx) {
				if (xfer->flags_int.control_xfr)
					temp.func = &musbotg_host_ctrl_data_tx;
				else
					temp.func = &musbotg_host_data_tx;
			} else {
				if (xfer->flags_int.control_xfr)
					temp.func = &musbotg_host_ctrl_data_rx;
				else
					temp.func = &musbotg_host_data_rx;
			}

		} else {
			if (tx) {
				if (xfer->flags_int.control_xfr)
					temp.func = &musbotg_dev_ctrl_data_tx;
				else
					temp.func = &musbotg_dev_data_tx;
			} else {
				if (xfer->flags_int.control_xfr)
					temp.func = &musbotg_dev_ctrl_data_rx;
				else
					temp.func = &musbotg_dev_data_rx;
			}
		}

		/* setup "pc" pointer */
		temp.pc = xfer->frbuffers + x;
	}
	while (x != xfer->nframes) {

		/* DATA0 / DATA1 message */

		temp.len = xfer->frlengths[x];

		x++;

		if (x == xfer->nframes) {
			if (xfer->flags_int.control_xfr) {
				if (xfer->flags_int.control_act) {
					temp.setup_alt_next = 0;
				}
			} else {
				temp.setup_alt_next = 0;
			}
		}
		if (temp.len == 0) {

			/* make sure that we send an USB packet */

			temp.short_pkt = 0;

		} else {

			if (xfer->flags_int.isochronous_xfr) {
				/* isochronous data transfer */
				/* don't force short */
				temp.short_pkt = 1;
			} else {
				/* regular data transfer */
				temp.short_pkt = (xfer->flags.force_short_xfer ? 0 : 1);
			}
		}

		musbotg_setup_standard_chain_sub(&temp);

		if (xfer->flags_int.isochronous_xfr) {
			temp.offset += temp.len;
		} else {
			/* get next Page Cache pointer */
			temp.pc = xfer->frbuffers + x;
		}
	}

	/* check for control transfer */
	if (xfer->flags_int.control_xfr) {

		/* always setup a valid "pc" pointer for status and sync */
		temp.pc = xfer->frbuffers + 0;
		temp.len = 0;
		temp.short_pkt = 0;
		temp.setup_alt_next = 0;

		/* check if we should append a status stage */
		if (!xfer->flags_int.control_act) {
			/*
			 * Send a DATA1 message and invert the current
			 * endpoint direction.
			 */
			if (sc->sc_mode == MUSB2_DEVICE_MODE)
				temp.func = &musbotg_dev_ctrl_status;
			else {
				if (xfer->endpointno & UE_DIR_IN)
					temp.func = musbotg_host_ctrl_status_tx;
				else
					temp.func = musbotg_host_ctrl_status_rx;
			}
			musbotg_setup_standard_chain_sub(&temp);
		}
	}
	/* must have at least one frame! */
	td = temp.td;
	xfer->td_transfer_last = td;
}