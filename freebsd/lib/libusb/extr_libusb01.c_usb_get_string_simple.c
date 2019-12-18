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

/* Variables and functions */
 int libusb20_dev_req_string_simple_sync (void*,int,char*,size_t) ; 
 int strlen (char*) ; 

int
usb_get_string_simple(usb_dev_handle * dev, int strindex,
    char *buf, size_t buflen)
{
	int err;

	if (dev == NULL)
		return (-1);

	if (buflen > 65535)
		buflen = 65535;

	err = libusb20_dev_req_string_simple_sync((void *)dev,
	    strindex, buf, buflen);

	if (err)
		return (-1);

	return (strlen(buf));
}