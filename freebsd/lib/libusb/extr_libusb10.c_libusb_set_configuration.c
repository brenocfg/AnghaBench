#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct libusb_device {int /*<<< orphan*/  dev_poll; int /*<<< orphan*/  ctx; } ;
struct libusb20_device {int dummy; } ;
struct TYPE_2__ {int bConfigurationValue; } ;
struct libusb20_config {TYPE_1__ desc; } ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  free (struct libusb20_config*) ; 
 int /*<<< orphan*/  libusb10_add_pollfd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct libusb20_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  libusb10_cancel_all_transfer (struct libusb_device*) ; 
 int /*<<< orphan*/  libusb10_remove_pollfd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct libusb20_config* libusb20_dev_alloc_config (struct libusb20_device*,int) ; 
 int /*<<< orphan*/  libusb20_dev_get_fd (struct libusb20_device*) ; 
 int libusb20_dev_set_config_index (struct libusb20_device*,int) ; 
 struct libusb_device* libusb_get_device (struct libusb20_device*) ; 

int
libusb_set_configuration(struct libusb20_device *pdev, int configuration)
{
	struct libusb20_config *pconf;
	struct libusb_device *dev;
	int err;
	uint8_t i;

	dev = libusb_get_device(pdev);
	if (dev == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if (configuration < 1) {
		/* unconfigure */
		i = 255;
	} else {
		for (i = 0; i != 255; i++) {
			uint8_t found;

			pconf = libusb20_dev_alloc_config(pdev, i);
			if (pconf == NULL)
				return (LIBUSB_ERROR_INVALID_PARAM);
			found = (pconf->desc.bConfigurationValue
			    == configuration);
			free(pconf);

			if (found)
				goto set_config;
		}
		return (LIBUSB_ERROR_INVALID_PARAM);
	}

set_config:

	libusb10_cancel_all_transfer(dev);

	libusb10_remove_pollfd(dev->ctx, &dev->dev_poll);

	err = libusb20_dev_set_config_index(pdev, i);

	libusb10_add_pollfd(dev->ctx, &dev->dev_poll, pdev, libusb20_dev_get_fd(pdev), POLLIN |
	    POLLOUT | POLLRDNORM | POLLWRNORM);

	return (err ? LIBUSB_ERROR_INVALID_PARAM : 0);
}