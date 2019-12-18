#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  usb_dev_handle ;
struct usb_device {int dummy; } ;
struct libusb20_device {struct usb_device* privLuData; } ;

/* Variables and functions */

struct usb_device *
usb_device(usb_dev_handle * dev)
{
	struct libusb20_device *pdev;

	pdev = (void *)dev;

	return (pdev->privLuData);
}