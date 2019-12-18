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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct usb_fs_init {int ep_index_max; int /*<<< orphan*/  pEndpoints; } ;
struct usb_fs_endpoint {int ep_index_max; int /*<<< orphan*/  pEndpoints; } ;
struct libusb20_device {int nTransfer; int /*<<< orphan*/  file; struct usb_fs_init* privBeData; } ;
typedef  int /*<<< orphan*/  fs_init ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_ERROR_NO_MEM ; 
 int LIBUSB20_ERROR_OTHER ; 
 int /*<<< orphan*/  USB_FS_INIT ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_fs_init*) ; 
 int /*<<< orphan*/  libusb20_pass_ptr (struct usb_fs_init*) ; 
 struct usb_fs_init* malloc (int) ; 
 int /*<<< orphan*/  memset (struct usb_fs_init*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ugen20_tr_renew(struct libusb20_device *pdev)
{
	struct usb_fs_init fs_init;
	struct usb_fs_endpoint *pfse;
	int error;
	uint32_t size;
	uint16_t nMaxTransfer;

	nMaxTransfer = pdev->nTransfer;
	error = 0;

	if (nMaxTransfer == 0) {
		goto done;
	}
	size = nMaxTransfer * sizeof(*pfse);

	if (pdev->privBeData == NULL) {
		pfse = malloc(size);
		if (pfse == NULL) {
			error = LIBUSB20_ERROR_NO_MEM;
			goto done;
		}
		pdev->privBeData = pfse;
	}
	/* reset endpoint data */
	memset(pdev->privBeData, 0, size);

	memset(&fs_init, 0, sizeof(fs_init));

	fs_init.pEndpoints = libusb20_pass_ptr(pdev->privBeData);
	fs_init.ep_index_max = nMaxTransfer;

	if (ioctl(pdev->file, IOUSB(USB_FS_INIT), &fs_init)) {
		error = LIBUSB20_ERROR_OTHER;
		goto done;
	}
done:
	return (error);
}