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
struct usb_fs_endpoint {scalar_t__ status; scalar_t__ isoc_time_complete; scalar_t__ aFrames; } ;
struct usb_fs_complete {int /*<<< orphan*/  ep_index; } ;
struct libusb20_transfer {int /*<<< orphan*/  status; scalar_t__ timeComplete; scalar_t__ aFrames; } ;
struct libusb20_device {struct libusb20_transfer* pTransfer; struct usb_fs_endpoint* privBeData; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_ERROR_OTHER ; 
 int /*<<< orphan*/  LIBUSB20_TRANSFER_CANCELLED ; 
 int /*<<< orphan*/  LIBUSB20_TRANSFER_COMPLETED ; 
 int /*<<< orphan*/  LIBUSB20_TRANSFER_ERROR ; 
 int /*<<< orphan*/  LIBUSB20_TRANSFER_STALL ; 
 int /*<<< orphan*/  LIBUSB20_TRANSFER_TIMED_OUT ; 
 scalar_t__ USB_ERR_CANCELLED ; 
 scalar_t__ USB_ERR_STALLED ; 
 scalar_t__ USB_ERR_TIMEOUT ; 
 int /*<<< orphan*/  USB_FS_COMPLETE ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_fs_complete*) ; 
 int /*<<< orphan*/  libusb20_tr_callback_wrapper (struct libusb20_transfer*) ; 

__attribute__((used)) static int
ugen20_process(struct libusb20_device *pdev)
{
	struct usb_fs_complete temp;
	struct usb_fs_endpoint *fsep;
	struct libusb20_transfer *xfer;

	while (1) {

	  if (ioctl(pdev->file, IOUSB(USB_FS_COMPLETE), &temp)) {
			if (errno == EBUSY) {
				break;
			} else {
				/* device detached */
				return (LIBUSB20_ERROR_OTHER);
			}
		}
		fsep = pdev->privBeData;
		xfer = pdev->pTransfer;
		fsep += temp.ep_index;
		xfer += temp.ep_index;

		/* update transfer status */

		if (fsep->status == 0) {
			xfer->aFrames = fsep->aFrames;
			xfer->timeComplete = fsep->isoc_time_complete;
			xfer->status = LIBUSB20_TRANSFER_COMPLETED;
		} else if (fsep->status == USB_ERR_CANCELLED) {
			xfer->aFrames = 0;
			xfer->timeComplete = 0;
			xfer->status = LIBUSB20_TRANSFER_CANCELLED;
		} else if (fsep->status == USB_ERR_STALLED) {
			xfer->aFrames = 0;
			xfer->timeComplete = 0;
			xfer->status = LIBUSB20_TRANSFER_STALL;
		} else if (fsep->status == USB_ERR_TIMEOUT) {
			xfer->aFrames = 0;
			xfer->timeComplete = 0;
			xfer->status = LIBUSB20_TRANSFER_TIMED_OUT;
		} else {
			xfer->aFrames = 0;
			xfer->timeComplete = 0;
			xfer->status = LIBUSB20_TRANSFER_ERROR;
		}
		libusb20_tr_callback_wrapper(xfer);
	}
	return (0);			/* done */
}