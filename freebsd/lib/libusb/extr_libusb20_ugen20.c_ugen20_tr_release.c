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
struct usb_fs_uninit {int dummy; } ;
struct libusb20_device {scalar_t__ nTransfer; int /*<<< orphan*/  file; int /*<<< orphan*/ * privBeData; } ;
typedef  int /*<<< orphan*/  fs_uninit ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_FS_UNINIT ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_fs_uninit*) ; 
 int /*<<< orphan*/  memset (struct usb_fs_uninit*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ugen20_tr_release(struct libusb20_device *pdev)
{
	struct usb_fs_uninit fs_uninit;

	if (pdev->nTransfer == 0) {
		return;
	}
	/* release all pending USB transfers */
	if (pdev->privBeData != NULL) {
		memset(&fs_uninit, 0, sizeof(fs_uninit));
		if (ioctl(pdev->file, IOUSB(USB_FS_UNINIT), &fs_uninit)) {
			/* ignore any errors of this kind */
		}
	}
	return;
}