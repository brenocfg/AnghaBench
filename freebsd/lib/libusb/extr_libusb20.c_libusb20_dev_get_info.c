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
struct usb_device_info {int dummy; } ;
struct libusb20_device {TYPE_1__* beMethods; } ;
struct TYPE_2__ {int (* dev_get_info ) (struct libusb20_device*,struct usb_device_info*) ;} ;

/* Variables and functions */
 int LIBUSB20_ERROR_INVALID_PARAM ; 
 int stub1 (struct libusb20_device*,struct usb_device_info*) ; 

int
libusb20_dev_get_info(struct libusb20_device *pdev,
    struct usb_device_info *pinfo)
{
	if (pinfo == NULL)
		return (LIBUSB20_ERROR_INVALID_PARAM);

	return (pdev->beMethods->dev_get_info(pdev, pinfo));
}