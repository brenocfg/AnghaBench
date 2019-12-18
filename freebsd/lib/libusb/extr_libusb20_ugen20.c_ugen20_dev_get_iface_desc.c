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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  ugd ;
struct usb_gen_descriptor {void* ugd_iface_index; void* ugd_maxlen; int /*<<< orphan*/  ugd_data; } ;
struct libusb20_device {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_ERROR_INVALID_PARAM ; 
 int /*<<< orphan*/  USB_GET_IFACE_DRIVER ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_gen_descriptor*) ; 
 int /*<<< orphan*/  libusb20_pass_ptr (char*) ; 
 int /*<<< orphan*/  memset (struct usb_gen_descriptor*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ugen20_dev_get_iface_desc(struct libusb20_device *pdev, 
    uint8_t iface_index, char *buf, uint8_t len)
{
	struct usb_gen_descriptor ugd;

	memset(&ugd, 0, sizeof(ugd));

	ugd.ugd_data = libusb20_pass_ptr(buf);
	ugd.ugd_maxlen = len;
	ugd.ugd_iface_index = iface_index;

	if (ioctl(pdev->file, IOUSB(USB_GET_IFACE_DRIVER), &ugd)) {
		return (LIBUSB20_ERROR_INVALID_PARAM);
	}
	return (0);
}