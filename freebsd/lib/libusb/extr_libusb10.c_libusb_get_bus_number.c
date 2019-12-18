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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  os_priv; } ;
typedef  TYPE_1__ libusb_device ;

/* Variables and functions */
 int /*<<< orphan*/  libusb20_dev_get_bus_number (int /*<<< orphan*/ ) ; 

uint8_t
libusb_get_bus_number(libusb_device *dev)
{
	if (dev == NULL)
		return (0);		/* should not happen */
	return (libusb20_dev_get_bus_number(dev->os_priv));
}