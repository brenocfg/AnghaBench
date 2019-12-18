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
typedef  int /*<<< orphan*/  usb_complete_t ;
struct usb_host_endpoint {int dummy; } ;
struct usb_device {int dummy; } ;
struct urb {int transfer_buffer_length; void* context; int /*<<< orphan*/  complete; void* transfer_buffer; struct usb_host_endpoint* endpoint; struct usb_device* dev; } ;

/* Variables and functions */

void
usb_fill_bulk_urb(struct urb *urb, struct usb_device *udev,
    struct usb_host_endpoint *uhe, void *buf,
    int length, usb_complete_t callback, void *arg)
{
	urb->dev = udev;
	urb->endpoint = uhe;
	urb->transfer_buffer = buf;
	urb->transfer_buffer_length = length;
	urb->complete = callback;
	urb->context = arg;
}