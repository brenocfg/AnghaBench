#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct libusb_transfer {int /*<<< orphan*/  status; int /*<<< orphan*/  endpoint; struct libusb_device_handle* dev_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tqe_prev; } ;
struct libusb_super_transfer {scalar_t__ state; TYPE_1__ entry; } ;
struct libusb_device_handle {int dummy; } ;
struct libusb_device {scalar_t__ device_is_gone; int /*<<< orphan*/  ctx; int /*<<< orphan*/  tr_head; } ;
struct libusb20_transfer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIBUSB_DEBUG_FUNCTION ; 
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_NOT_FOUND ; 
 scalar_t__ LIBUSB_SUPER_XFER_ST_PEND ; 
 int /*<<< orphan*/  LIBUSB_TRANSFER_CANCELLED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct libusb_super_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  libusb10_complete_transfer (struct libusb20_transfer*,struct libusb_super_transfer*,int /*<<< orphan*/ ) ; 
 struct libusb20_transfer* libusb10_get_transfer (struct libusb_device_handle*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  libusb10_submit_transfer_sub (struct libusb_device_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb10_wakeup_event_loop (int /*<<< orphan*/ ) ; 
 struct libusb_super_transfer* libusb20_tr_get_priv_sc1 (struct libusb20_transfer*) ; 
 int /*<<< orphan*/  libusb20_tr_set_priv_sc1 (struct libusb20_transfer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb20_tr_stop (struct libusb20_transfer*) ; 
 struct libusb_device* libusb_get_device (struct libusb_device_handle*) ; 

int
libusb_cancel_transfer(struct libusb_transfer *uxfer)
{
	struct libusb20_transfer *pxfer0;
	struct libusb20_transfer *pxfer1;
	struct libusb_super_transfer *sxfer;
	struct libusb_device *dev;
	struct libusb_device_handle *devh;
	uint8_t endpoint;
	int retval;

	if (uxfer == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	/* check if not initialised */
	if ((devh = uxfer->dev_handle) == NULL)
		return (LIBUSB_ERROR_NOT_FOUND);

	endpoint = uxfer->endpoint;

	dev = libusb_get_device(devh);

	DPRINTF(dev->ctx, LIBUSB_DEBUG_FUNCTION, "libusb_cancel_transfer enter");

	sxfer = (struct libusb_super_transfer *)(
	    (uint8_t *)uxfer - sizeof(*sxfer));

	retval = 0;

	CTX_LOCK(dev->ctx);

	pxfer0 = libusb10_get_transfer(devh, endpoint, 0);
	pxfer1 = libusb10_get_transfer(devh, endpoint, 1);

	if (sxfer->state != LIBUSB_SUPER_XFER_ST_PEND) {
		/* only update the transfer status */
		uxfer->status = LIBUSB_TRANSFER_CANCELLED;
		retval = LIBUSB_ERROR_NOT_FOUND;
	} else if (sxfer->entry.tqe_prev != NULL) {
		/* we are lucky - transfer is on a queue */
		TAILQ_REMOVE(&dev->tr_head, sxfer, entry);
		sxfer->entry.tqe_prev = NULL;
		libusb10_complete_transfer(NULL,
		    sxfer, LIBUSB_TRANSFER_CANCELLED);
		/* make sure our event loop spins the done handler */
		libusb10_wakeup_event_loop(dev->ctx);
	} else if (pxfer0 == NULL || pxfer1 == NULL) {
		/* not started */
		retval = LIBUSB_ERROR_NOT_FOUND;
	} else if (libusb20_tr_get_priv_sc1(pxfer0) == sxfer) {
		libusb10_complete_transfer(pxfer0,
		    sxfer, LIBUSB_TRANSFER_CANCELLED);
		if (dev->device_is_gone != 0) {
			/* clear transfer pointer */
			libusb20_tr_set_priv_sc1(pxfer0, NULL);
			/* make sure our event loop spins the done handler */
			libusb10_wakeup_event_loop(dev->ctx);
		} else {
			libusb20_tr_stop(pxfer0);
			/* make sure the queue doesn't stall */
			libusb10_submit_transfer_sub(devh, endpoint);
		}
	} else if (libusb20_tr_get_priv_sc1(pxfer1) == sxfer) {
		libusb10_complete_transfer(pxfer1,
		    sxfer, LIBUSB_TRANSFER_CANCELLED);
		/* check if handle is still active */
		if (dev->device_is_gone != 0) {
			/* clear transfer pointer */
			libusb20_tr_set_priv_sc1(pxfer1, NULL);
			/* make sure our event loop spins the done handler */
			libusb10_wakeup_event_loop(dev->ctx);
		} else {
			libusb20_tr_stop(pxfer1);
			/* make sure the queue doesn't stall */
			libusb10_submit_transfer_sub(devh, endpoint);
		}
	} else {
		/* not started */
		retval = LIBUSB_ERROR_NOT_FOUND;
	}

	CTX_UNLOCK(dev->ctx);

	DPRINTF(dev->ctx, LIBUSB_DEBUG_FUNCTION, "libusb_cancel_transfer leave");

	return (retval);
}