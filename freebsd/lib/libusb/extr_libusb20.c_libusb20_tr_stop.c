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
struct libusb20_transfer {int is_cancel; TYPE_2__* pdev; int /*<<< orphan*/  is_pending; int /*<<< orphan*/  is_opened; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* tr_cancel_async ) (struct libusb20_transfer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct libusb20_transfer*) ; 

void
libusb20_tr_stop(struct libusb20_transfer *xfer)
{
	if (!xfer->is_opened) {
		/* transfer is not opened */
		return;
	}
	if (!xfer->is_pending) {
		/* transfer not pending */
		return;
	}
	if (xfer->is_cancel) {
		/* already cancelling */
		return;
	}
	xfer->is_cancel = 1;		/* we are cancelling */

	xfer->pdev->methods->tr_cancel_async(xfer);
	return;
}