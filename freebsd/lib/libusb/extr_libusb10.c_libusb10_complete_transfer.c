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
struct libusb_transfer {int status; int /*<<< orphan*/  dev_handle; } ;
struct libusb_super_transfer {int /*<<< orphan*/  state; } ;
struct libusb_device {TYPE_1__* ctx; } ;
struct libusb20_transfer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tr_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBUSB_SUPER_XFER_ST_NONE ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct libusb_super_transfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  libusb20_tr_set_priv_sc1 (struct libusb20_transfer*,int /*<<< orphan*/ *) ; 
 struct libusb_device* libusb_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
libusb10_complete_transfer(struct libusb20_transfer *pxfer,
    struct libusb_super_transfer *sxfer, int status)
{
	struct libusb_transfer *uxfer;
	struct libusb_device *dev;

	uxfer = (struct libusb_transfer *)(
	    ((uint8_t *)sxfer) + sizeof(*sxfer));

	if (pxfer != NULL)
		libusb20_tr_set_priv_sc1(pxfer, NULL);

	/* set transfer status */
	uxfer->status = status;

	/* update super transfer state */
	sxfer->state = LIBUSB_SUPER_XFER_ST_NONE;

	dev = libusb_get_device(uxfer->dev_handle);

	TAILQ_INSERT_TAIL(&dev->ctx->tr_done, sxfer, entry);
}