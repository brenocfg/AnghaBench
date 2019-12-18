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
struct libusb20_device {int /*<<< orphan*/  file_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_ERROR_OTHER ; 
 int /*<<< orphan*/  USB_IFACE_DRIVER_DETACH ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
ugen20_detach_kernel_driver(struct libusb20_device *pdev,
    uint8_t iface_index)
{
	int temp = iface_index;

	if (ioctl(pdev->file_ctrl, IOUSB(USB_IFACE_DRIVER_DETACH), &temp)) {
		return (LIBUSB20_ERROR_OTHER);
	}
	return (0);			/* kernel driver is detached */
}