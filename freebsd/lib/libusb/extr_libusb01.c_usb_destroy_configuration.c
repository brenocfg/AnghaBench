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
typedef  size_t uint8_t ;
struct TYPE_2__ {size_t bNumConfigurations; } ;
struct usb_device {struct usb_config_descriptor* config; TYPE_1__ descriptor; } ;
struct usb_config_descriptor {struct usb_config_descriptor* interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct usb_config_descriptor*) ; 

void
usb_destroy_configuration(struct usb_device *dev)
{
	uint8_t c;

	if (dev->config == NULL) {
		return;
	}
	for (c = 0; c != dev->descriptor.bNumConfigurations; c++) {
		struct usb_config_descriptor *cf = &dev->config[c];

		if (cf->interface != NULL) {
			free(cf->interface);
			cf->interface = NULL;
		}
	}

	free(dev->config);
	dev->config = NULL;
	return;
}