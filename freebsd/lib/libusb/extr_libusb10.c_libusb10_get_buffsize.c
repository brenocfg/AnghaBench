#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct libusb20_device {int dummy; } ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ libusb_transfer ;

/* Variables and functions */
#define  LIBUSB20_SPEED_FULL 132 
#define  LIBUSB20_SPEED_LOW 131 
#define  LIBUSB20_SPEED_SUPER 130 
#define  LIBUSB_TRANSFER_TYPE_CONTROL 129 
#define  LIBUSB_TRANSFER_TYPE_ISOCHRONOUS 128 
 int libusb20_dev_get_speed (struct libusb20_device*) ; 

__attribute__((used)) static int
libusb10_get_buffsize(struct libusb20_device *pdev, libusb_transfer *xfer)
{
	int ret;
	int usb_speed;

	usb_speed = libusb20_dev_get_speed(pdev);

	switch (xfer->type) {
	case LIBUSB_TRANSFER_TYPE_ISOCHRONOUS:
		ret = 0;		/* kernel will auto-select */
		break;
	case LIBUSB_TRANSFER_TYPE_CONTROL:
		ret = 1024;
		break;
	default:
		switch (usb_speed) {
		case LIBUSB20_SPEED_LOW:
			ret = 256;
			break;
		case LIBUSB20_SPEED_FULL:
			ret = 4096;
			break;
		case LIBUSB20_SPEED_SUPER:
			ret = 65536;
			break;
		default:
			ret = 16384;
			break;
		}
		break;
	}
	return (ret);
}