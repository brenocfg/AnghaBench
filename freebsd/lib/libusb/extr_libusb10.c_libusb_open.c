#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct libusb20_device {int dummy; } ;
typedef  struct libusb20_device libusb_device_handle ;
struct TYPE_6__ {int /*<<< orphan*/  dev_poll; struct libusb20_device* os_priv; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ libusb_device ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_NO_MEM ; 
 int /*<<< orphan*/  LIBUSB_NUM_SW_ENDPOINTS ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  libusb10_add_pollfd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct libusb20_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  libusb10_wakeup_event_loop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb20_dev_get_fd (struct libusb20_device*) ; 
 int libusb20_dev_open (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* libusb_ref_device (TYPE_1__*) ; 
 int /*<<< orphan*/  libusb_unref_device (TYPE_1__*) ; 

int
libusb_open(libusb_device *dev, libusb_device_handle **devh)
{
	libusb_context *ctx = dev->ctx;
	struct libusb20_device *pdev = dev->os_priv;
	int err;

	if (devh == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	/* set default device handle value */
	*devh = NULL;

	dev = libusb_ref_device(dev);
	if (dev == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	err = libusb20_dev_open(pdev, LIBUSB_NUM_SW_ENDPOINTS);
	if (err) {
		libusb_unref_device(dev);
		return (LIBUSB_ERROR_NO_MEM);
	}
	libusb10_add_pollfd(ctx, &dev->dev_poll, pdev, libusb20_dev_get_fd(pdev), POLLIN |
	    POLLOUT | POLLRDNORM | POLLWRNORM);

	/* make sure our event loop detects the new device */
	libusb10_wakeup_event_loop(ctx);

	*devh = pdev;

	return (0);
}