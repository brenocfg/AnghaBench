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
struct libusb_transfer {int /*<<< orphan*/ * dev_handle; int /*<<< orphan*/  endpoint; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tqe_prev; } ;
struct libusb_super_transfer {int /*<<< orphan*/  state; TYPE_1__ entry; } ;
struct libusb_device {scalar_t__ device_is_gone; int /*<<< orphan*/  ctx; int /*<<< orphan*/  tr_head; } ;
struct libusb20_transfer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  LIBUSB_DEBUG_FUNCTION ; 
 int LIBUSB_ERROR_BUSY ; 
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_NO_DEVICE ; 
 int LIBUSB_ERROR_OTHER ; 
 int /*<<< orphan*/  LIBUSB_SUPER_XFER_ST_PEND ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct libusb_super_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 struct libusb20_transfer* libusb10_get_transfer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  libusb10_submit_transfer_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct libusb_super_transfer* libusb20_tr_get_priv_sc1 (struct libusb20_transfer*) ; 
 struct libusb_device* libusb_get_device (int /*<<< orphan*/ *) ; 

int
libusb_submit_transfer(struct libusb_transfer *uxfer)
{
	struct libusb20_transfer *pxfer0;
	struct libusb20_transfer *pxfer1;
	struct libusb_super_transfer *sxfer;
	struct libusb_device *dev;
	uint8_t endpoint;
	int err;

	if (uxfer == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if (uxfer->dev_handle == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	endpoint = uxfer->endpoint;

	dev = libusb_get_device(uxfer->dev_handle);

	DPRINTF(dev->ctx, LIBUSB_DEBUG_FUNCTION, "libusb_submit_transfer enter");

	sxfer = (struct libusb_super_transfer *)(
	    (uint8_t *)uxfer - sizeof(*sxfer));

	CTX_LOCK(dev->ctx);

	pxfer0 = libusb10_get_transfer(uxfer->dev_handle, endpoint, 0);
	pxfer1 = libusb10_get_transfer(uxfer->dev_handle, endpoint, 1);

	if (pxfer0 == NULL || pxfer1 == NULL) {
		err = LIBUSB_ERROR_OTHER;
	} else if ((sxfer->entry.tqe_prev != NULL) ||
	    (libusb20_tr_get_priv_sc1(pxfer0) == sxfer) ||
	    (libusb20_tr_get_priv_sc1(pxfer1) == sxfer)) {
		err = LIBUSB_ERROR_BUSY;
	} else if (dev->device_is_gone != 0) {
		err = LIBUSB_ERROR_NO_DEVICE;
	} else {

		/* set pending state */
		sxfer->state = LIBUSB_SUPER_XFER_ST_PEND;

		/* insert transfer into transfer head list */
		TAILQ_INSERT_TAIL(&dev->tr_head, sxfer, entry);

		/* start work transfers */
		libusb10_submit_transfer_sub(
		    uxfer->dev_handle, endpoint);

		err = 0;		/* success */
	}

	CTX_UNLOCK(dev->ctx);

	DPRINTF(dev->ctx, LIBUSB_DEBUG_FUNCTION, "libusb_submit_transfer leave %d", err);

	return (err);
}