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
struct libusb20_device {int file; int file_ctrl; int /*<<< orphan*/ * privBeData; scalar_t__ nTransfer; } ;
typedef  int /*<<< orphan*/  fs_uninit ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_FS_UNINIT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct usb_fs_uninit*) ; 
 int /*<<< orphan*/  memset (struct usb_fs_uninit*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ugen20_close_device(struct libusb20_device *pdev)
{
	struct usb_fs_uninit fs_uninit;

	if (pdev->privBeData) {
		memset(&fs_uninit, 0, sizeof(fs_uninit));
		if (ioctl(pdev->file, IOUSB(USB_FS_UNINIT), &fs_uninit)) {
			/* ignore this error */
		}
		free(pdev->privBeData);
	}
	pdev->nTransfer = 0;
	pdev->privBeData = NULL;
	close(pdev->file);
	close(pdev->file_ctrl);
	pdev->file = -1;
	pdev->file_ctrl = -1;
	return (0);			/* success */
}