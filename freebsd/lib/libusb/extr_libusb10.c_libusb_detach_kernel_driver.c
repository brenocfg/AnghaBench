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
struct libusb20_device {int dummy; } ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_OTHER ; 
 int libusb20_dev_detach_kernel_driver (struct libusb20_device*,int) ; 

int
libusb_detach_kernel_driver(struct libusb20_device *pdev, int interface)
{
	int err;

	if (pdev == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	err = libusb20_dev_detach_kernel_driver(
	    pdev, interface);

	return (err ? LIBUSB_ERROR_OTHER : 0);
}