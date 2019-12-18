#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct usb_xfer {void* td_transfer_last; struct octusb_td* td_transfer_cache; } ;
struct octusb_td {scalar_t__ remainder; scalar_t__ alt_next; struct octusb_td* obj_next; scalar_t__ error_any; scalar_t__ (* func ) (struct octusb_td*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  octusb_standard_done (struct usb_xfer*) ; 
 scalar_t__ stub1 (struct octusb_td*) ; 

__attribute__((used)) static uint8_t
octusb_xfer_do_fifo(struct usb_xfer *xfer)
{
	struct octusb_td *td;

	DPRINTFN(8, "\n");

	td = xfer->td_transfer_cache;

	while (1) {
		if ((td->func) (td)) {
			/* operation in progress */
			break;
		}
		if (((void *)td) == xfer->td_transfer_last) {
			goto done;
		}
		if (td->error_any) {
			goto done;
		} else if (td->remainder > 0) {
			/*
			 * We had a short transfer. If there is no
			 * alternate next, stop processing !
			 */
			if (td->alt_next == 0)
				goto done;
		}
		/*
		 * Fetch the next transfer descriptor and transfer
		 * some flags to the next transfer descriptor
		 */
		td = td->obj_next;
		xfer->td_transfer_cache = td;
	}
	return (1);			/* not complete */

done:
	/* compute all actual lengths */

	octusb_standard_done(xfer);

	return (0);			/* complete */
}