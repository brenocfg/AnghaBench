#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct libusb20_device {int dummy; } ;
struct TYPE_4__ {int claimed_interfaces; int /*<<< orphan*/  dev_poll; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ libusb_device ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_NOT_FOUND ; 
 int LIBUSB_ERROR_OTHER ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  libusb10_add_pollfd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct libusb20_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  libusb10_cancel_all_transfer (TYPE_1__*) ; 
 int /*<<< orphan*/  libusb10_remove_pollfd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb20_dev_get_fd (struct libusb20_device*) ; 
 int libusb20_dev_set_alt_index (struct libusb20_device*,int,int) ; 
 TYPE_1__* libusb_get_device (struct libusb20_device*) ; 

int
libusb_set_interface_alt_setting(struct libusb20_device *pdev,
    int interface_number, int alternate_setting)
{
	libusb_device *dev;
	int err = 0;

	dev = libusb_get_device(pdev);
	if (dev == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if (interface_number < 0 || interface_number > 31)
		return (LIBUSB_ERROR_INVALID_PARAM);

	CTX_LOCK(dev->ctx);
	if (!(dev->claimed_interfaces & (1 << interface_number)))
		err = LIBUSB_ERROR_NOT_FOUND;
	CTX_UNLOCK(dev->ctx);

	if (err)
		return (err);

	libusb10_cancel_all_transfer(dev);

	libusb10_remove_pollfd(dev->ctx, &dev->dev_poll);

	err = libusb20_dev_set_alt_index(pdev,
	    interface_number, alternate_setting);

	libusb10_add_pollfd(dev->ctx, &dev->dev_poll,
	    pdev, libusb20_dev_get_fd(pdev),
	    POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM);

	return (err ? LIBUSB_ERROR_OTHER : 0);
}