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
struct libusb20_transfer {int /*<<< orphan*/  (* callback ) (struct libusb20_transfer*) ;int /*<<< orphan*/  status; scalar_t__ is_draining; scalar_t__ is_pending; scalar_t__ is_restart; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBUSB20_TRANSFER_DRAINED ; 
 int /*<<< orphan*/  LIBUSB20_TRANSFER_START ; 
 int /*<<< orphan*/  stub1 (struct libusb20_transfer*) ; 
 int /*<<< orphan*/  stub2 (struct libusb20_transfer*) ; 

void
libusb20_tr_callback_wrapper(struct libusb20_transfer *xfer)
{
	;				/* style fix */

repeat:

	if (!xfer->is_pending) {
		xfer->status = LIBUSB20_TRANSFER_START;
	} else {
		xfer->is_pending = 0;
	}

	xfer->callback(xfer);

	if (xfer->is_restart) {
		xfer->is_restart = 0;
		goto repeat;
	}
	if (xfer->is_draining &&
	    (!xfer->is_pending)) {
		xfer->is_draining = 0;
		xfer->status = LIBUSB20_TRANSFER_DRAINED;
		xfer->callback(xfer);
	}
	return;
}