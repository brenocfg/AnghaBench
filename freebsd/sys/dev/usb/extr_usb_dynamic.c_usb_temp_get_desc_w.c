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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device_request {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ERR_STALLED ; 

__attribute__((used)) static usb_error_t
usb_temp_get_desc_w(struct usb_device *udev, struct usb_device_request *req, const void **pPtr, uint16_t *pLength)
{
	/* stall */
	return (USB_ERR_STALLED);
}