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
typedef  int uint8_t ;
struct libusb20_transfer {int dummy; } ;
struct libusb20_device {int dummy; } ;

/* Variables and functions */
 int LIBUSB20_ENDPOINT_ADDRESS_MASK ; 
 int LIBUSB20_ENDPOINT_DIR_MASK ; 
 struct libusb20_transfer* libusb20_tr_get_pointer (struct libusb20_device*,int) ; 

__attribute__((used)) static struct libusb20_transfer *
libusb10_get_transfer(struct libusb20_device *pdev,
    uint8_t endpoint, uint8_t xfer_index)
{
	xfer_index &= 1;	/* double buffering */

	xfer_index |= (endpoint & LIBUSB20_ENDPOINT_ADDRESS_MASK) * 4;

	if (endpoint & LIBUSB20_ENDPOINT_DIR_MASK) {
		/* this is an IN endpoint */
		xfer_index |= 2;
	}
	return (libusb20_tr_get_pointer(pdev, xfer_index));
}