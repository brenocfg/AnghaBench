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
typedef  int /*<<< orphan*/  temp ;
struct usb_fs_start {scalar_t__ ep_index; } ;
struct usb_fs_endpoint {int timeout; int /*<<< orphan*/  flags; int /*<<< orphan*/  nFrames; } ;
struct libusb20_transfer {int flags; int timeout; TYPE_1__* pdev; scalar_t__ trIndex; int /*<<< orphan*/  nFrames; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; struct usb_fs_endpoint* privBeData; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_TRANSFER_DO_CLEAR_STALL ; 
 int LIBUSB20_TRANSFER_FORCE_SHORT ; 
 int LIBUSB20_TRANSFER_MULTI_SHORT_NOT_OK ; 
 int LIBUSB20_TRANSFER_SINGLE_SHORT_NOT_OK ; 
 int /*<<< orphan*/  USB_FS_FLAG_CLEAR_STALL ; 
 int /*<<< orphan*/  USB_FS_FLAG_FORCE_SHORT ; 
 int /*<<< orphan*/  USB_FS_FLAG_MULTI_SHORT_OK ; 
 int /*<<< orphan*/  USB_FS_FLAG_SINGLE_SHORT_OK ; 
 int /*<<< orphan*/  USB_FS_START ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_fs_start*) ; 
 int /*<<< orphan*/  memset (struct usb_fs_start*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ugen20_tr_submit(struct libusb20_transfer *xfer)
{
	struct usb_fs_start temp;
	struct usb_fs_endpoint *fsep;

	memset(&temp, 0, sizeof(temp));

	fsep = xfer->pdev->privBeData;
	fsep += xfer->trIndex;

	fsep->nFrames = xfer->nFrames;
	fsep->flags = 0;
	if (!(xfer->flags & LIBUSB20_TRANSFER_SINGLE_SHORT_NOT_OK)) {
		fsep->flags |= USB_FS_FLAG_SINGLE_SHORT_OK;
	}
	if (!(xfer->flags & LIBUSB20_TRANSFER_MULTI_SHORT_NOT_OK)) {
		fsep->flags |= USB_FS_FLAG_MULTI_SHORT_OK;
	}
	if (xfer->flags & LIBUSB20_TRANSFER_FORCE_SHORT) {
		fsep->flags |= USB_FS_FLAG_FORCE_SHORT;
	}
	if (xfer->flags & LIBUSB20_TRANSFER_DO_CLEAR_STALL) {
		fsep->flags |= USB_FS_FLAG_CLEAR_STALL;
	}
	/* NOTE: The "fsep->timeout" variable is 16-bit. */
	if (xfer->timeout > 65535)
		fsep->timeout = 65535;
	else
		fsep->timeout = xfer->timeout;

	temp.ep_index = xfer->trIndex;

	if (ioctl(xfer->pdev->file, IOUSB(USB_FS_START), &temp)) {
		/* ignore any errors - should never happen */
	}
	return;				/* success */
}