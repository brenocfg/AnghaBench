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
typedef  scalar_t__ usb_error_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ isochronous_xfr; scalar_t__ short_frames_ok; } ;
struct usb_xfer {size_t aframes; size_t nframes; scalar_t__* frlengths; struct dwc_otg_td* td_transfer_cache; TYPE_2__ flags_int; TYPE_1__* endpoint; } ;
struct dwc_otg_td {scalar_t__ remainder; int error_any; struct dwc_otg_td* obj_next; scalar_t__ alt_next; scalar_t__ error_stall; int /*<<< orphan*/  toggle; } ;
struct TYPE_3__ {int /*<<< orphan*/  toggle_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 scalar_t__ USB_ERR_IOERROR ; 
 scalar_t__ USB_ERR_STALLED ; 

__attribute__((used)) static usb_error_t
dwc_otg_standard_done_sub(struct usb_xfer *xfer)
{
	struct dwc_otg_td *td;
	uint32_t len;
	usb_error_t error;

	DPRINTFN(9, "\n");

	td = xfer->td_transfer_cache;

	do {
		len = td->remainder;

		/* store last data toggle */
		xfer->endpoint->toggle_next = td->toggle;

		if (xfer->aframes != xfer->nframes) {
			/*
			 * Verify the length and subtract
			 * the remainder from "frlengths[]":
			 */
			if (len > xfer->frlengths[xfer->aframes]) {
				td->error_any = 1;
			} else {
				xfer->frlengths[xfer->aframes] -= len;
			}
		}
		/* Check for transfer error */
		if (td->error_any) {
			/* the transfer is finished */
			error = (td->error_stall ?
			    USB_ERR_STALLED : USB_ERR_IOERROR);
			td = NULL;
			break;
		}
		/* Check for short transfer */
		if (len > 0) {
			if (xfer->flags_int.short_frames_ok ||
			    xfer->flags_int.isochronous_xfr) {
				/* follow alt next */
				if (td->alt_next) {
					td = td->obj_next;
				} else {
					td = NULL;
				}
			} else {
				/* the transfer is finished */
				td = NULL;
			}
			error = 0;
			break;
		}
		td = td->obj_next;

		/* this USB frame is complete */
		error = 0;
		break;

	} while (0);

	/* update transfer cache */

	xfer->td_transfer_cache = td;

	return (error);
}