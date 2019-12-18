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
struct usb_endpoint {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
xhci_ep_uninit(struct usb_device *udev, struct usb_endpoint *ep)
{

}