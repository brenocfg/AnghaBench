#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_13__ {scalar_t__ control_act; scalar_t__ control_xfr; scalar_t__ isochronous_xfr; scalar_t__ control_hdr; int /*<<< orphan*/  control_stall; scalar_t__ short_frames_ok; } ;
struct TYPE_8__ {scalar_t__ force_short_xfer; } ;
struct usb_xfer {int endpointno; scalar_t__* frlengths; int nframes; unsigned int fps_shift; TYPE_5__* endpoint; struct saf1761_otg_td* td_transfer_first; struct saf1761_otg_td* td_transfer_last; int /*<<< orphan*/ * frbuffers; TYPE_6__ flags_int; TYPE_1__ flags; TYPE_3__* xroot; struct saf1761_otg_td** td_start; struct saf1761_otg_td* td_transfer_cache; int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  sumlen; int /*<<< orphan*/  address; } ;
struct saf1761_otg_td {int uframe; int set_toggle; int toggle; } ;
struct saf1761_otg_std_temp {scalar_t__ offset; int setup_alt_next; int did_stall; scalar_t__ len; int short_pkt; struct saf1761_otg_td* td; int /*<<< orphan*/ * func; int /*<<< orphan*/ * pc; struct saf1761_otg_td* td_next; int /*<<< orphan*/  max_frame_size; } ;
struct saf1761_otg_softc {int dummy; } ;
struct TYPE_9__ {scalar_t__ usb_mode; } ;
struct TYPE_14__ {scalar_t__ speed; TYPE_2__ flags; } ;
struct TYPE_12__ {scalar_t__ toggle_next; TYPE_4__* edesc; } ;
struct TYPE_11__ {int bmAttributes; } ;
struct TYPE_10__ {TYPE_7__* udev; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct saf1761_otg_softc* SAF1761_OTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int SAF1761_READ_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOTG_FRINDEX ; 
 int SOTG_FRINDEX_MASK ; 
 int UE_ADDR ; 
 int UE_DIR_IN ; 
 int /*<<< orphan*/  UE_GET_ADDR (int) ; 
 int UE_INTERRUPT ; 
 int UE_ISOCHRONOUS ; 
 int UE_XFERTYPE ; 
 scalar_t__ USB_MODE_HOST ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  saf1761_device_data_rx ; 
 int /*<<< orphan*/  saf1761_device_data_tx ; 
 int /*<<< orphan*/  saf1761_device_data_tx_sync ; 
 int /*<<< orphan*/  saf1761_device_setup_rx ; 
 int /*<<< orphan*/  saf1761_host_bulk_data_rx ; 
 int /*<<< orphan*/  saf1761_host_bulk_data_tx ; 
 int /*<<< orphan*/  saf1761_host_intr_data_rx ; 
 int /*<<< orphan*/  saf1761_host_intr_data_tx ; 
 int /*<<< orphan*/  saf1761_host_isoc_data_rx ; 
 int /*<<< orphan*/  saf1761_host_isoc_data_tx ; 
 int /*<<< orphan*/  saf1761_host_setup_tx ; 
 int /*<<< orphan*/  saf1761_otg_setup_standard_chain_sub (struct saf1761_otg_std_temp*) ; 
 int /*<<< orphan*/  usbd_get_speed (TYPE_7__*) ; 

__attribute__((used)) static void
saf1761_otg_setup_standard_chain(struct usb_xfer *xfer)
{
	struct saf1761_otg_std_temp temp;
	struct saf1761_otg_softc *sc;
	struct saf1761_otg_td *td;
	uint32_t x;
	uint8_t ep_no;
	uint8_t ep_type;
	uint8_t need_sync;
	uint8_t is_host;
	uint8_t uframe_start;
	uint8_t uframe_interval;

	DPRINTFN(9, "addr=%d endpt=%d sumlen=%d speed=%d\n",
	    xfer->address, UE_GET_ADDR(xfer->endpointno),
	    xfer->sumlen, usbd_get_speed(xfer->xroot->udev));

	temp.max_frame_size = xfer->max_frame_size;

	td = xfer->td_start[0];
	xfer->td_transfer_first = td;
	xfer->td_transfer_cache = td;

	/* setup temp */

	temp.pc = NULL;
	temp.td = NULL;
	temp.td_next = xfer->td_start[0];
	temp.offset = 0;
	temp.setup_alt_next = xfer->flags_int.short_frames_ok ||
	    xfer->flags_int.isochronous_xfr;
	temp.did_stall = !xfer->flags_int.control_stall;

	is_host = (xfer->xroot->udev->flags.usb_mode == USB_MODE_HOST);

	sc = SAF1761_OTG_BUS2SC(xfer->xroot->bus);
	ep_no = (xfer->endpointno & UE_ADDR);
	ep_type = (xfer->endpoint->edesc->bmAttributes & UE_XFERTYPE);

	/* check if we should prepend a setup message */

	if (xfer->flags_int.control_xfr) {
		if (xfer->flags_int.control_hdr) {

			if (is_host)
				temp.func = &saf1761_host_setup_tx;
			else
				temp.func = &saf1761_device_setup_rx;

			temp.len = xfer->frlengths[0];
			temp.pc = xfer->frbuffers + 0;
			temp.short_pkt = temp.len ? 1 : 0;
			/* check for last frame */
			if (xfer->nframes == 1) {
				/* no STATUS stage yet, SETUP is last */
				if (xfer->flags_int.control_act)
					temp.setup_alt_next = 0;
			}
			saf1761_otg_setup_standard_chain_sub(&temp);
		}
		x = 1;
	} else {
		x = 0;
	}

	uframe_start = 0;
	uframe_interval = 0;

	if (x != xfer->nframes) {
		if (xfer->endpointno & UE_DIR_IN) {
			if (is_host) {
				if (ep_type == UE_INTERRUPT) {
					temp.func = &saf1761_host_intr_data_rx;
				} else if (ep_type == UE_ISOCHRONOUS) {
					temp.func = &saf1761_host_isoc_data_rx;
					uframe_start = (SAF1761_READ_LE_4(sc, SOTG_FRINDEX) + 8) &
					    (SOTG_FRINDEX_MASK & ~7);
					if (xfer->xroot->udev->speed == USB_SPEED_HIGH)
						uframe_interval = 1U << xfer->fps_shift;
					else
						uframe_interval = 8U;
				} else {
					temp.func = &saf1761_host_bulk_data_rx;
				}
				need_sync = 0;
			} else {
				temp.func = &saf1761_device_data_tx;
				need_sync = 1;
			}
		} else {
			if (is_host) {
				if (ep_type == UE_INTERRUPT) {
					temp.func = &saf1761_host_intr_data_tx;
				} else if (ep_type == UE_ISOCHRONOUS) {
					temp.func = &saf1761_host_isoc_data_tx;
					uframe_start = (SAF1761_READ_LE_4(sc, SOTG_FRINDEX) + 8) &
					    (SOTG_FRINDEX_MASK & ~7);
					if (xfer->xroot->udev->speed == USB_SPEED_HIGH)
						uframe_interval = 1U << xfer->fps_shift;
					else
						uframe_interval = 8U;
				} else {
					temp.func = &saf1761_host_bulk_data_tx;
				}
				need_sync = 0;
			} else {
				temp.func = &saf1761_device_data_rx;
				need_sync = 0;
			}
		}

		/* setup "pc" pointer */
		temp.pc = xfer->frbuffers + x;
	} else {
		need_sync = 0;
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

			/* regular data transfer */

			temp.short_pkt = (xfer->flags.force_short_xfer) ? 0 : 1;
		}

		saf1761_otg_setup_standard_chain_sub(&temp);

		if (xfer->flags_int.isochronous_xfr) {
			temp.offset += temp.len;

			/* stamp the starting point for this transaction */
			temp.td->uframe = uframe_start;

			/* advance to next */
			uframe_start += uframe_interval;
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
			if (xfer->endpointno & UE_DIR_IN) {
				if (is_host) {
					temp.func = &saf1761_host_bulk_data_tx;
					need_sync = 0;
				} else {
					temp.func = &saf1761_device_data_rx;
					need_sync = 0;
				}
			} else {
				if (is_host) {
					temp.func = &saf1761_host_bulk_data_rx;
					need_sync = 0;
				} else {
					temp.func = &saf1761_device_data_tx;
					need_sync = 1;
				}
			}
			temp.len = 0;
			temp.short_pkt = 0;

			saf1761_otg_setup_standard_chain_sub(&temp);

			/* data toggle should be DATA1 */
			td = temp.td;
			td->set_toggle = 1;

			if (need_sync) {
				/* we need a SYNC point after TX */
				temp.func = &saf1761_device_data_tx_sync;
				saf1761_otg_setup_standard_chain_sub(&temp);
			}
		}
	} else {
		if (need_sync) {
			temp.pc = xfer->frbuffers + 0;
			temp.len = 0;
			temp.short_pkt = 0;
			temp.setup_alt_next = 0;

			/* we need a SYNC point after TX */
			temp.func = &saf1761_device_data_tx_sync;
			saf1761_otg_setup_standard_chain_sub(&temp);
		}
	}

	/* must have at least one frame! */
	td = temp.td;
	xfer->td_transfer_last = td;

	if (is_host) {
		/* get first again */
		td = xfer->td_transfer_first;
		td->toggle = (xfer->endpoint->toggle_next ? 1 : 0);
	}
}