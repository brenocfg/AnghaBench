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
struct usb_device {TYPE_1__* bus; } ;
struct usb_bus_methods {int /*<<< orphan*/  (* get_power_mode ) (struct usb_device*,int*) ;} ;
typedef  int int8_t ;
struct TYPE_2__ {struct usb_bus_methods* methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usb_device*,int*) ; 

uint8_t
usbd_filter_power_mode(struct usb_device *udev, uint8_t power_mode)
{
	const struct usb_bus_methods *mtod;
	int8_t temp;

	mtod = udev->bus->methods;
	temp = -1;

	if (mtod->get_power_mode != NULL)
		(mtod->get_power_mode) (udev, &temp);

	/* check if we should not filter */
	if (temp < 0)
		return (power_mode);

	/* use fixed power mode given by hardware driver */
	return (temp);
}