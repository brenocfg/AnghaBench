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
struct libusb20_transfer {scalar_t__ maxPacketLen; scalar_t__ maxTotalLength; scalar_t__ maxFrames; scalar_t__ timeout; scalar_t__ aFrames; scalar_t__ nFrames; scalar_t__ flags; scalar_t__ status; scalar_t__ is_restart; scalar_t__ is_draining; scalar_t__ is_cancel; scalar_t__ is_pending; scalar_t__ is_opened; int /*<<< orphan*/ * priv_sc1; int /*<<< orphan*/ * priv_sc0; scalar_t__ ppBuffer; scalar_t__ pLength; TYPE_2__* pdev; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {int (* tr_close ) (struct libusb20_transfer*) ;} ;

/* Variables and functions */
 int LIBUSB20_ERROR_OTHER ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int stub1 (struct libusb20_transfer*) ; 

int
libusb20_tr_close(struct libusb20_transfer *xfer)
{
	int error;

	if (!xfer->is_opened) {
		return (LIBUSB20_ERROR_OTHER);
	}
	error = xfer->pdev->methods->tr_close(xfer);

	if (xfer->pLength) {
		free(xfer->pLength);
	}
	if (xfer->ppBuffer) {
		free(xfer->ppBuffer);
	}
	/* reset variable fields in case the transfer is opened again */
	xfer->priv_sc0 = NULL;
	xfer->priv_sc1 = NULL;
	xfer->is_opened = 0;
	xfer->is_pending = 0;
	xfer->is_cancel = 0;
	xfer->is_draining = 0;
	xfer->is_restart = 0;
	xfer->status = 0;
	xfer->flags = 0;
	xfer->nFrames = 0;
	xfer->aFrames = 0;
	xfer->timeout = 0;
	xfer->maxFrames = 0;
	xfer->maxTotalLength = 0;
	xfer->maxPacketLen = 0;
	return (error);
}