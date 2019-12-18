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
typedef  int uint32_t ;
struct libusb20_device {int dummy; } ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ libusb_transfer ;

/* Variables and functions */
 int LIBUSB20_MAX_FRAME_PRE_SCALE ; 
#define  LIBUSB_TRANSFER_TYPE_CONTROL 129 
#define  LIBUSB_TRANSFER_TYPE_ISOCHRONOUS 128 

__attribute__((used)) static uint32_t
libusb10_get_maxframe(struct libusb20_device *pdev, libusb_transfer *xfer)
{
	uint32_t ret;

	switch (xfer->type) {
	case LIBUSB_TRANSFER_TYPE_ISOCHRONOUS:
		ret = 60 | LIBUSB20_MAX_FRAME_PRE_SCALE;	/* 60ms */
		break;
	case LIBUSB_TRANSFER_TYPE_CONTROL:
		ret = 2;
		break;
	default:
		ret = 1;
		break;
	}
	return (ret);
}