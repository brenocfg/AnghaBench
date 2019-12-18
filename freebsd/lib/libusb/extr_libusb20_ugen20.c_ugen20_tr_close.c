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
struct usb_fs_close {int /*<<< orphan*/  ep_index; } ;
struct libusb20_transfer {TYPE_1__* pdev; int /*<<< orphan*/  trIndex; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_ERROR_INVALID_PARAM ; 
 int /*<<< orphan*/  USB_FS_CLOSE ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_fs_close*) ; 
 int /*<<< orphan*/  memset (struct usb_fs_close*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ugen20_tr_close(struct libusb20_transfer *xfer)
{
	struct usb_fs_close temp;

	memset(&temp, 0, sizeof(temp));

	temp.ep_index = xfer->trIndex;

	if (ioctl(xfer->pdev->file, IOUSB(USB_FS_CLOSE), &temp)) {
		return (LIBUSB20_ERROR_INVALID_PARAM);
	}
	return (0);			/* success */
}