#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_8__ {scalar_t__ control_act; scalar_t__ control_xfr; scalar_t__ isochronous_xfr; scalar_t__ control_hdr; scalar_t__ short_frames_ok; } ;
struct TYPE_7__ {scalar_t__ force_short_xfer; } ;
struct usb_xfer {int endpointno; scalar_t__* frlengths; int nframes; TYPE_5__* endpoint; struct octusb_td* td_transfer_last; TYPE_3__ flags_int; int /*<<< orphan*/ * frbuffers; TYPE_2__ flags; struct octusb_td* td_transfer_cache; struct octusb_td* td_transfer_first; struct octusb_td** td_start; TYPE_1__* xroot; int /*<<< orphan*/  sumlen; int /*<<< orphan*/  address; } ;
struct octusb_td {TYPE_4__* qh; } ;
struct octusb_std_temp {scalar_t__ offset; scalar_t__ len; int short_pkt; struct octusb_td* td; scalar_t__ setup_alt_next; int /*<<< orphan*/ * pc; int /*<<< orphan*/ * func; struct octusb_td* td_next; } ;
struct TYPE_10__ {scalar_t__ toggle_next; } ;
struct TYPE_9__ {int ep_toggle_next; scalar_t__ ep_allocated; } ;
struct TYPE_6__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UE_DIR_IN ; 
 int /*<<< orphan*/  UE_GET_ADDR (int) ; 
 int /*<<< orphan*/  octusb_host_control_data_rx ; 
 int /*<<< orphan*/  octusb_host_control_data_tx ; 
 int /*<<< orphan*/  octusb_host_control_header_tx ; 
 int /*<<< orphan*/  octusb_host_control_status_tx ; 
 int /*<<< orphan*/  octusb_non_control_data_rx ; 
 int /*<<< orphan*/  octusb_non_control_data_tx ; 
 int /*<<< orphan*/  octusb_setup_standard_chain_sub (struct octusb_std_temp*) ; 
 int /*<<< orphan*/  usbd_get_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
octusb_setup_standard_chain(struct usb_xfer *xfer)
{
	struct octusb_std_temp temp;
	struct octusb_td *td;
	uint32_t x;

	DPRINTFN(9, "addr=%d endpt=%d sumlen=%d speed=%d\n",
	    xfer->address, UE_GET_ADDR(xfer->endpointno),
	    xfer->sumlen, usbd_get_speed(xfer->xroot->udev));

	/* setup starting point */
	td = xfer->td_start[0];
	xfer->td_transfer_first = td;
	xfer->td_transfer_cache = td;

	temp.td = NULL;
	temp.td_next = td;
	temp.setup_alt_next = xfer->flags_int.short_frames_ok;
	temp.offset = 0;

	/* check if we should prepend a setup message */

	if (xfer->flags_int.control_xfr) {

		if (xfer->flags_int.control_hdr) {

			temp.func = &octusb_host_control_header_tx;
			temp.len = xfer->frlengths[0];
			temp.pc = xfer->frbuffers + 0;
			temp.short_pkt = temp.len ? 1 : 0;

			/* check for last frame */
			if (xfer->nframes == 1) {
				/*
				 * no STATUS stage yet, SETUP is
				 * last
				 */
				if (xfer->flags_int.control_act)
					temp.setup_alt_next = 0;
			}
			octusb_setup_standard_chain_sub(&temp);
		}
		x = 1;
	} else {
		x = 0;
	}

	if (x != xfer->nframes) {
		if (xfer->endpointno & UE_DIR_IN) {
			if (xfer->flags_int.control_xfr)
				temp.func = &octusb_host_control_data_rx;
			else
				temp.func = &octusb_non_control_data_rx;
		} else {
			if (xfer->flags_int.control_xfr)
				temp.func = &octusb_host_control_data_tx;
			else
				temp.func = &octusb_non_control_data_tx;
		}

		/* setup "pc" pointer */
		temp.pc = xfer->frbuffers + x;
	}
	while (x != xfer->nframes) {

		/* DATA0 or DATA1 message */

		temp.len = xfer->frlengths[x];

		x++;

		if (x == xfer->nframes) {
			if (xfer->flags_int.control_xfr) {
				/* no STATUS stage yet, DATA is last */
				if (xfer->flags_int.control_act)
					temp.setup_alt_next = 0;
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

		octusb_setup_standard_chain_sub(&temp);

		if (xfer->flags_int.isochronous_xfr) {
			/* get next data offset */
			temp.offset += temp.len;
		} else {
			/* get next Page Cache pointer */
			temp.pc = xfer->frbuffers + x;
		}
	}

	/* check if we should append a status stage */

	if (xfer->flags_int.control_xfr &&
	    !xfer->flags_int.control_act) {

		temp.func = &octusb_host_control_status_tx;
		temp.len = 0;
		temp.pc = NULL;
		temp.short_pkt = 0;
		temp.setup_alt_next = 0;

		octusb_setup_standard_chain_sub(&temp);
	}
	/* must have at least one frame! */
	td = temp.td;
	xfer->td_transfer_last = td;

	/* properly setup QH */

	td->qh->ep_allocated = 0;
	td->qh->ep_toggle_next = xfer->endpoint->toggle_next ? 1 : 0;
}