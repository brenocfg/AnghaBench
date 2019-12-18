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
struct libusb20_device {int dummy; } ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_OTHER ; 
 int libusb20_dev_get_iface_desc (struct libusb20_device*,int,char*,int) ; 
 char* strstr (char*,char*) ; 

int
libusb_get_driver(struct libusb20_device *pdev, int interface,
    char *name, int namelen)
{
	char *ptr;
	int err;

	if (pdev == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);
	if (namelen < 1)
		return (LIBUSB_ERROR_INVALID_PARAM);
	if (namelen > 255)
		namelen = 255;

	err = libusb20_dev_get_iface_desc(
	    pdev, interface, name, namelen);

	if (err != 0)
		return (LIBUSB_ERROR_OTHER);

	/* we only want the driver name */
	ptr = strstr(name, ":");
	if (ptr != NULL)
		*ptr = 0;

	return (0);
}