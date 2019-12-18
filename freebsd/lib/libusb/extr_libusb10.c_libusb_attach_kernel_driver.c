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

int
libusb_attach_kernel_driver(struct libusb20_device *pdev, int interface)
{
	if (pdev == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);
	/* stub - currently not supported by libusb20 */
	return (0);
}