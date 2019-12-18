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
struct libusb20_transfer {int is_restart; scalar_t__ is_cancel; scalar_t__ is_pending; int /*<<< orphan*/  is_opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  libusb20_tr_callback_wrapper (struct libusb20_transfer*) ; 

void
libusb20_tr_start(struct libusb20_transfer *xfer)
{
	if (!xfer->is_opened) {
		/* transfer is not opened */
		return;
	}
	if (xfer->is_pending) {
		if (xfer->is_cancel) {
			/* cancelling - restart */
			xfer->is_restart = 1;
		}
		/* transfer not pending */
		return;
	}
	/* get into the callback */
	libusb20_tr_callback_wrapper(xfer);
	return;
}