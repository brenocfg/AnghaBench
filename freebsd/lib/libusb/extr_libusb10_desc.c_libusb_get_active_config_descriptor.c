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
typedef  int /*<<< orphan*/  uint8_t ;
struct libusb_config_descriptor {int dummy; } ;
struct libusb20_device {int dummy; } ;
struct TYPE_4__ {struct libusb20_device* os_priv; } ;
typedef  TYPE_1__ libusb_device ;

/* Variables and functions */
 int /*<<< orphan*/  libusb20_dev_get_config_index (struct libusb20_device*) ; 
 int libusb_get_config_descriptor (TYPE_1__*,int /*<<< orphan*/ ,struct libusb_config_descriptor**) ; 

int
libusb_get_active_config_descriptor(libusb_device *dev,
    struct libusb_config_descriptor **config)
{
	struct libusb20_device *pdev;
	uint8_t config_index;

	pdev = dev->os_priv;
	config_index = libusb20_dev_get_config_index(pdev);

	return (libusb_get_config_descriptor(dev, config_index, config));
}