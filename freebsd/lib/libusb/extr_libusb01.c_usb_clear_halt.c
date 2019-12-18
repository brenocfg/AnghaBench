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
struct libusb20_transfer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  libusb20_tr_clear_stall_sync (struct libusb20_transfer*) ; 
 struct libusb20_transfer* usb_get_transfer_by_ep_no (int /*<<< orphan*/ *,unsigned int) ; 

int
usb_clear_halt(usb_dev_handle * dev, unsigned int ep)
{
	struct libusb20_transfer *xfer;

	xfer = usb_get_transfer_by_ep_no(dev, ep);
	if (xfer == NULL)
		return (-1);

	libusb20_tr_clear_stall_sync(xfer);

	return (0);
}