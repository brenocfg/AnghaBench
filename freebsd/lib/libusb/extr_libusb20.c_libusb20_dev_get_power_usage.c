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
typedef  scalar_t__ uint16_t ;
struct libusb20_device {TYPE_1__* methods; } ;
struct TYPE_2__ {int (* get_power_usage ) (struct libusb20_device*,scalar_t__*) ;} ;

/* Variables and functions */
 int stub1 (struct libusb20_device*,scalar_t__*) ; 

uint16_t
libusb20_dev_get_power_usage(struct libusb20_device *pdev)
{
	int error;
	uint16_t power_usage;

	error = pdev->methods->get_power_usage(pdev, &power_usage);
	if (error)
		power_usage = 0;
	return (power_usage);
}