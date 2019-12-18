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
struct libusb20_device {int dummy; } ;

/* Variables and functions */
 int libusb20_dev_get_iface_desc (struct libusb20_device*,int,char*,int) ; 
 char* strstr (char*,char*) ; 

int
usb_get_driver_np(usb_dev_handle * dev, int interface, char *name, int namelen)
{
	struct libusb20_device *pdev;
	char *ptr;
	int err;

	pdev = (void *)dev;

	if (pdev == NULL)
		return (-1);
	if (namelen < 1)
		return (-1);
	if (namelen > 255)
		namelen = 255;

	err = libusb20_dev_get_iface_desc(pdev, interface, name, namelen);
	if (err != 0)
		return (-1);

	/* we only want the driver name */
	ptr = strstr(name, ":");
	if (ptr != NULL)
		*ptr = 0;

	return (0);
}