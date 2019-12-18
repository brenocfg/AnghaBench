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
typedef  int /*<<< orphan*/  usb_timeout_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_host_endpoint {int dummy; } ;
struct usb_device {int dummy; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,struct usb_host_endpoint*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_linux_wait_complete ; 
 int usb_setup_endpoint (struct usb_device*,struct usb_host_endpoint*,int) ; 
 int usb_start_wait_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
usb_bulk_msg(struct usb_device *udev, struct usb_host_endpoint *uhe,
    void *data, int len, uint16_t *pactlen, usb_timeout_t timeout)
{
	struct urb *urb;
	int err;

	if (uhe == NULL)
		return (-EINVAL);
	if (len < 0)
		return (-EINVAL);

	err = usb_setup_endpoint(udev, uhe, 4096 /* bytes */);
	if (err)
		return (err);

	urb = usb_alloc_urb(0, 0);
	if (urb == NULL)
		return (-ENOMEM);

	usb_fill_bulk_urb(urb, udev, uhe, data, len,
	    usb_linux_wait_complete, NULL);

	err = usb_start_wait_urb(urb, timeout, pactlen);

	usb_free_urb(urb);

	return (err);
}