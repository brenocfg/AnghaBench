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
struct TYPE_3__ {int bNumConfigurations; } ;
struct usb_device {TYPE_2__* config; TYPE_1__ descriptor; } ;
struct TYPE_4__ {int bConfigurationValue; } ;

/* Variables and functions */
 int libusb20_dev_set_config_index (void*,int) ; 
 struct usb_device* usb_device (int /*<<< orphan*/ *) ; 

int
usb_set_configuration(usb_dev_handle * udev, int bConfigurationValue)
{
	struct usb_device *dev;
	int err;
	uint8_t i;

	/*
	 * Need to translate from "bConfigurationValue" to
	 * configuration index:
	 */

	if (bConfigurationValue == 0) {
		/* unconfigure */
		i = 255;
	} else {
		/* lookup configuration index */
		dev = usb_device(udev);

		/* check if the configuration array is not there */
		if (dev->config == NULL) {
			return (-1);
		}
		for (i = 0;; i++) {
			if (i == dev->descriptor.bNumConfigurations) {
				/* "bConfigurationValue" not found */
				return (-1);
			}
			if ((dev->config + i)->bConfigurationValue ==
			    bConfigurationValue) {
				break;
			}
		}
	}

	err = libusb20_dev_set_config_index((void *)udev, i);

	if (err)
		return (-1);

	return (0);
}