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
struct usb_xfer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int /*<<< orphan*/  uhci_device_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhci_device_isoc_close(struct usb_xfer *xfer)
{
	uhci_device_done(xfer, USB_ERR_CANCELLED);
}