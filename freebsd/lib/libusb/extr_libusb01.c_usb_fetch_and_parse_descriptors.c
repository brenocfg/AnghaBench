#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_dev_handle ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int bNumConfigurations; } ;
struct usb_device {int /*<<< orphan*/ * config; TYPE_1__ descriptor; } ;
struct usb_config_descriptor {int dummy; } ;
struct libusb20_device {TYPE_2__* methods; } ;
struct TYPE_4__ {int (* get_config_desc_full ) (struct libusb20_device*,int**,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct libusb20_device*,int**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_destroy_configuration (struct usb_device*) ; 
 struct usb_device* usb_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_parse_configuration (int /*<<< orphan*/ *,int*) ; 

void
usb_fetch_and_parse_descriptors(usb_dev_handle * udev)
{
	struct usb_device *dev;
	struct libusb20_device *pdev;
	uint8_t *ptr;
	int error;
	uint32_t size;
	uint16_t len;
	uint8_t x;

	if (udev == NULL) {
		/* be NULL safe */
		return;
	}
	dev = usb_device(udev);
	pdev = (void *)udev;

	if (dev->descriptor.bNumConfigurations == 0) {
		/* invalid device */
		return;
	}
	size = dev->descriptor.bNumConfigurations *
	    sizeof(struct usb_config_descriptor);

	dev->config = malloc(size);
	if (dev->config == NULL) {
		/* out of memory */
		return;
	}
	memset(dev->config, 0, size);

	for (x = 0; x != dev->descriptor.bNumConfigurations; x++) {

		error = (pdev->methods->get_config_desc_full) (
		    pdev, &ptr, &len, x);

		if (error) {
			usb_destroy_configuration(dev);
			return;
		}
		usb_parse_configuration(dev->config + x, ptr);

		/* free config buffer */
		free(ptr);
	}
	return;
}