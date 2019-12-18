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
typedef  int usb_timeout_t ;
typedef  int uint32_t ;
struct usb_device {TYPE_1__* bus; } ;
struct usb_bus_methods {int /*<<< orphan*/  (* get_dma_delay ) (struct usb_device*,int*) ;} ;
struct TYPE_2__ {struct usb_bus_methods* methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usb_device*,int*) ; 

usb_timeout_t
usbd_get_dma_delay(struct usb_device *udev)
{
	const struct usb_bus_methods *mtod;
	uint32_t temp;

	mtod = udev->bus->methods;
	temp = 0;

	if (mtod->get_dma_delay) {
		(mtod->get_dma_delay) (udev, &temp);
		/*
		 * Round up and convert to milliseconds. Note that we use
		 * 1024 milliseconds per second. to save a division.
		 */
		temp += 0x3FF;
		temp /= 0x400;
	}
	return (temp);
}