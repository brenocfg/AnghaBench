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
struct libusb20_device {scalar_t__ auto_detach; } ;
struct TYPE_3__ {int claimed_interfaces; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ libusb_device ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int libusb_detach_kernel_driver (struct libusb20_device*,int) ; 
 TYPE_1__* libusb_get_device (struct libusb20_device*) ; 

int
libusb_claim_interface(struct libusb20_device *pdev, int interface_number)
{
	libusb_device *dev;
	int err = 0;

	dev = libusb_get_device(pdev);
	if (dev == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if (interface_number < 0 || interface_number > 31)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if (pdev->auto_detach != 0) {
		err = libusb_detach_kernel_driver(pdev, interface_number);
		if (err != 0)
			goto done;
	}

	CTX_LOCK(dev->ctx);
	dev->claimed_interfaces |= (1 << interface_number);
	CTX_UNLOCK(dev->ctx);
done:
	return (err);
}