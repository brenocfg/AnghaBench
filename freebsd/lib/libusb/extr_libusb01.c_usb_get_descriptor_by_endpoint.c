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
typedef  int uint8_t ;

/* Variables and functions */
 int USB_ENDPOINT_IN ; 
 int /*<<< orphan*/  USB_REQ_GET_DESCRIPTOR ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int usb_control_msg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int,int) ; 

int
usb_get_descriptor_by_endpoint(usb_dev_handle * udev, int ep, uint8_t type,
    uint8_t ep_index, void *buf, int size)
{
	memset(buf, 0, size);

	if (udev == NULL)
		return (-1);

	if (size > 65535)
		size = 65535;

	return (usb_control_msg(udev, ep | USB_ENDPOINT_IN,
	    USB_REQ_GET_DESCRIPTOR, (type << 8) + ep_index, 0,
	    buf, size, 1000));
}